#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "parser.tab.h"

/* Flex buffer API — allows scanning an in-memory buffer instead of a file.
   This is the portable, safe approach: no tmpfile(), no rewind(stdin). */
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_bytes(const char *bytes, int len);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
extern void yy_switch_to_buffer(YY_BUFFER_STATE buffer);

extern int yyparse(void);
extern FILE *yyin;
extern ASTNode *g_root_ast;
extern TokenList *g_token_list;
extern DiagnosticList *g_diagnostic_list;
extern int g_syntax_error_count;
extern int g_lexical_error_count;
extern char **g_source_lines;
extern int g_source_line_count;

static void print_usage(const char *prog) {
    fprintf(stderr, "Usage: %s [--json | --tokens-only] [input_file]\n", prog);
}

/* Read entire stream into a malloc'd buffer. Returns NULL on failure.
   *out_len receives the number of bytes read (not counting a synthetic '\n'
   we append so the lexer always sees a final newline). */
static char *read_all(FILE *f, size_t *out_len) {
    size_t cap = 4096;
    size_t len = 0;
    char *buf = (char *)malloc(cap);
    if (!buf) return NULL;

    int c;
    while ((c = fgetc(f)) != EOF) {
        if (len + 2 >= cap) {   /* +2: room for the char + trailing '\n' */
            cap *= 2;
            char *nb = (char *)realloc(buf, cap);
            if (!nb) { free(buf); return NULL; }
            buf = nb;
        }
        buf[len++] = (char)c;
    }
    /* Ensure the buffer ends with a newline so the lexer emits the final EOL */
    if (len == 0 || buf[len - 1] != '\n') {
        buf[len++] = '\n';
    }
    buf[len] = '\0';
    *out_len = len;
    return buf;
}

/* Split a buffer (by '\n') into g_source_lines.
   Both '\r\n' and '\n' are handled; trailing '\r' is stripped. */
static void split_source_lines(const char *buf, size_t len) {
    size_t lines_cap = 64;
    g_source_lines = (char **)malloc(lines_cap * sizeof(char *));
    g_source_line_count = 0;

    const char *start = buf;
    const char *end   = buf + len;

    while (start <= end) {
        const char *nl = memchr(start, '\n', (size_t)(end - start));
        size_t line_len = nl ? (size_t)(nl - start) : (size_t)(end - start);

        /* Strip trailing '\r' */
        while (line_len > 0 && start[line_len - 1] == '\r') line_len--;

        if ((size_t)g_source_line_count >= lines_cap) {
            lines_cap *= 2;
            g_source_lines = (char **)realloc(g_source_lines,
                                               lines_cap * sizeof(char *));
        }
        char *copied = (char *)malloc(line_len + 1);
        memcpy(copied, start, line_len);
        copied[line_len] = '\0';
        g_source_lines[g_source_line_count++] = copied;

        if (!nl) break;
        start = nl + 1;
    }
}

int main(int argc, char *argv[]) {
    bool tokens_only = false;
    const char *input_path = NULL;

    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--json") == 0) {
            tokens_only = false;
        } else if (strcmp(argv[i], "--tokens-only") == 0) {
            tokens_only = true;
        } else if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            print_usage(argv[0]);
            return 0;
        } else if (argv[i][0] != '-') {
            input_path = argv[i];
        } else {
            fprintf(stderr, "Unknown option: %s\n", argv[i]);
            print_usage(argv[0]);
            return 1;
        }
    }

    /* Open input */
    FILE *in = stdin;
    if (input_path) {
        in = fopen(input_path, "r");
        if (!in) {
            fprintf(stderr, "Error: Cannot open input file '%s'\n", input_path);
            return 1;
        }
    }

    /* Read ALL content into a memory buffer.
       This is portable: it works on stdin, regular files, and inside Docker
       containers where tmpfile() may fail due to /tmp restrictions. */
    size_t src_len = 0;
    char *src_buf = read_all(in, &src_len);

    if (input_path && in != stdin) {
        fclose(in);
    }

    if (!src_buf) {
        fprintf(stderr, "Error: Failed to read input (out of memory)\n");
        return 1;
    }

    /* Build the source-line array for diagnostic snippets */
    split_source_lines(src_buf, src_len);

    /* Initialize data structures BEFORE parsing begins */
    g_token_list        = token_list_create();
    g_diagnostic_list   = diagnostic_list_create();
    g_syntax_error_count  = 0;
    g_lexical_error_count = 0;

    /* Feed the in-memory buffer to Flex — no file I/O needed */
    YY_BUFFER_STATE lex_buf = yy_scan_bytes(src_buf, (int)src_len);
    free(src_buf);  /* Flex copied the bytes; we can free our buffer */

    /* Parse */
    int parse_result = yyparse();

    yy_delete_buffer(lex_buf);

    bool has_errors = (g_syntax_error_count > 0 || g_lexical_error_count > 0 || parse_result != 0);
    bool is_success = !has_errors;

    if (tokens_only) {
        printf("%-18s | %-20s | %-6s | %-6s\n", "TOKEN TYPE", "LEXEME", "LINE", "COLUMN");
        printf("-------------------+----------------------+--------+-------\n");
        for (size_t i = 0; i < g_token_list->count; i++) {
            printf("%-18s | %-20s | %-6d | %-6d\n",
                g_token_list->items[i].type,
                g_token_list->items[i].lexeme,
                g_token_list->items[i].line,
                g_token_list->items[i].column);
        }
    } else {
        /* JSON Mode */
        printf("{\n");
        printf("  \"success\": %s,\n", is_success ? "true" : "false");
        printf("  \"status\": \"%s\",\n", is_success ? "ACCEPTED" : "REJECTED");

        /* Tokens Array */
        printf("  \"tokens\": [\n");
        for (size_t i = 0; i < g_token_list->count; i++) {
            char *esc_type = json_escape_string(g_token_list->items[i].type);
            char *esc_lex  = json_escape_string(g_token_list->items[i].lexeme);
            printf("    { \"type\": \"%s\", \"lexeme\": \"%s\", \"line\": %d, \"column\": %d }%s\n",
                esc_type,
                esc_lex,
                g_token_list->items[i].line,
                g_token_list->items[i].column,
                (i + 1 < g_token_list->count) ? "," : "");
            free(esc_type);
            free(esc_lex);
        }
        printf("  ],\n");

        /* Diagnostics Array */
        printf("  \"diagnostics\": [\n");
        for (size_t i = 0; i < g_diagnostic_list->count; i++) {
            char *esc_type = json_escape_string(g_diagnostic_list->items[i].type);
            char *esc_msg  = json_escape_string(g_diagnostic_list->items[i].message);
            char *esc_snip = json_escape_string(g_diagnostic_list->items[i].snippet);
            printf("    {\n");
            printf("      \"type\": \"%s\",\n", esc_type);
            printf("      \"message\": \"%s\",\n", esc_msg);
            printf("      \"line\": %d,\n", g_diagnostic_list->items[i].line);
            printf("      \"column\": %d,\n", g_diagnostic_list->items[i].column);
            printf("      \"snippet\": \"%s\"\n", esc_snip);
            printf("    }%s\n", (i + 1 < g_diagnostic_list->count) ? "," : "");
            free(esc_type);
            free(esc_msg);
            free(esc_snip);
        }
        printf("  ],\n");

        /* AST */
        printf("  \"ast\": ");
        if (is_success && g_root_ast) {
            print_ast_json(stdout, g_root_ast, 2);
            printf(",\n");
        } else {
            printf("null,\n");
        }

        /* Statistics */
        printf("  \"statistics\": {\n");
        printf("    \"tokenCount\": %zu,\n", g_token_list->count);
        printf("    \"errorCount\": %d,\n", g_syntax_error_count + g_lexical_error_count);
        printf("    \"lexicalErrorCount\": %d,\n", g_lexical_error_count);
        printf("    \"syntaxErrorCount\": %d,\n", g_syntax_error_count);
        printf("    \"lineCount\": %d,\n", g_source_line_count);
        printf("    \"parseStatus\": \"%s\"\n", is_success ? "ACCEPTED" : "REJECTED");
        printf("  }\n");

        printf("}\n");
    }

    /* Cleanup */
    if (g_root_ast) {
        free_ast(g_root_ast);
        g_root_ast = NULL;
    }
    if (g_token_list) {
        token_list_free(g_token_list);
        g_token_list = NULL;
    }
    if (g_diagnostic_list) {
        diagnostic_list_free(g_diagnostic_list);
        g_diagnostic_list = NULL;
    }
    for (int i = 0; i < g_source_line_count; i++) {
        free(g_source_lines[i]);
    }
    free(g_source_lines);
    g_source_lines = NULL;

    fflush(stdout);
    fflush(stderr);

    return is_success ? 0 : 1;
}
