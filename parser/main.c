#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "ast.h"
#include "parser.tab.h"

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

    /* Open input file or read from stdin */
    FILE *in = stdin;
    if (input_path) {
        in = fopen(input_path, "r");
        if (!in) {
            fprintf(stderr, "Error: Cannot open input file '%s'\n", input_path);
            return 1;
        }
    }

    /* Read all lines to buffer for source line snippets and line counting */
    size_t lines_cap = 64;
    g_source_lines = (char **)malloc(lines_cap * sizeof(char *));
    g_source_line_count = 0;

    char line_buf[4096];
    /* We also write the buffer to a temp file or memstream so lexer can scan it */
    FILE *mem_in = tmpfile();
    if (!mem_in) {
        mem_in = in;
    }

    while (fgets(line_buf, sizeof(line_buf), in)) {
        if ((size_t)g_source_line_count >= lines_cap) {
            lines_cap *= 2;
            g_source_lines = (char **)realloc(g_source_lines, lines_cap * sizeof(char *));
        }
        /* Strip trailing newline for clean snippet storage */
        size_t l = strlen(line_buf);
        if (mem_in != in) {
            fputs(line_buf, mem_in);
        }
        while (l > 0 && (line_buf[l - 1] == '\r' || line_buf[l - 1] == '\n')) {
            line_buf[--l] = '\0';
        }
        char *copied = (char *)malloc(l + 1);
        memcpy(copied, line_buf, l + 1);
        g_source_lines[g_source_line_count++] = copied;
    }

    if (input_path && in != stdin) {
        fclose(in);
    }

    if (mem_in != in) {
        rewind(mem_in);
        yyin = mem_in;
    } else {
        rewind(in);
        yyin = in;
    }

    /* Initialize data structures */
    g_token_list = token_list_create();
    g_diagnostic_list = diagnostic_list_create();
    g_syntax_error_count = 0;
    g_lexical_error_count = 0;

    /* Parse */
    int parse_result = yyparse();

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
            char *esc_lex = json_escape_string(g_token_list->items[i].lexeme);
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
            char *esc_msg = json_escape_string(g_diagnostic_list->items[i].message);
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

    if (mem_in && mem_in != stdin) {
        fclose(mem_in);
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

    return is_success ? 0 : 1;
}
