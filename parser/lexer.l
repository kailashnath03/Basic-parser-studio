%{
#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif
#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ast.h"
#include "parser.tab.h"

int yycolno = 1;
SourceLocation current_token_loc = {1, 1};

extern TokenList *g_token_list;
extern DiagnosticList *g_diagnostic_list;
extern int g_lexical_error_count;
extern const char *get_source_line_snippet(int line);

static int last_was_eol = 1;
static int eof_emitted = 0;

static void update_loc(void) {
    current_token_loc.line = yylineno;
    current_token_loc.column = yycolno;
    yycolno += yyleng;
    last_was_eol = 0;
}

static void record_tok(const char *type, const char *lexeme) {
    if (g_token_list) {
        token_list_append(g_token_list, type, lexeme, current_token_loc.line, current_token_loc.column);
    }
}

static char *unescape_basic_string(const char *raw, int len) {
    if (len < 2) return safe_strdup("");
    char *buf = (char *)malloc(len);
    int j = 0;
    for (int i = 1; i < len - 1; i++) {
        if (raw[i] == '\"' && raw[i+1] == '\"') {
            buf[j++] = '\"';
            i++;
        } else if (raw[i] == '\\' && i + 1 < len - 1) {
            i++;
            switch (raw[i]) {
                case 'n': buf[j++] = '\n'; break;
                case 't': buf[j++] = '\t'; break;
                case 'r': buf[j++] = '\r'; break;
                case '\\': buf[j++] = '\\'; break;
                case '\"': buf[j++] = '\"'; break;
                default: buf[j++] = raw[i]; break;
            }
        } else {
            buf[j++] = raw[i];
        }
    }
    buf[j] = '\0';
    return buf;
}

%}

%option noyywrap
%option yylineno
%option case-insensitive
%option nounput
%option noinput

DIGIT       [0-9]
INT         {DIGIT}+
FLOAT       ({DIGIT}+\.{DIGIT}*|\.{DIGIT}+)([eE][+-]?{DIGIT}+)?|{DIGIT}+[eE][+-]?{DIGIT}+
IDENT       [a-zA-Z][a-zA-Z0-9_]*[$%!]?
WHITESPACE  [ \t\f\v]+
EOL         (\r?\n)+

%%

{WHITESPACE} {
    yycolno += yyleng;
}

{EOL} {
    current_token_loc.line = yylineno - 1 > 0 ? yylineno - 1 : 1;
    current_token_loc.column = yycolno;
    yycolno = 1;
    last_was_eol = 1;
    record_tok("EOL", "\\n");
    return TOKEN_EOL;
}

":" {
    update_loc();
    record_tok("COLON", ":");
    return TOKEN_COLON;
}

";" {
    update_loc();
    record_tok("SEMICOLON", ";");
    return ';';
}

"," {
    update_loc();
    record_tok("COMMA", ",");
    return ',';
}

"(" {
    update_loc();
    record_tok("LPAREN", "(");
    return '(';
}

")" {
    update_loc();
    record_tok("RPAREN", ")");
    return ')';
}

"+" {
    update_loc();
    record_tok("PLUS", "+");
    return '+';
}

"-" {
    update_loc();
    record_tok("MINUS", "-");
    return '-';
}

"*" {
    update_loc();
    record_tok("MULTIPLY", "*");
    return '*';
}

"/" {
    update_loc();
    record_tok("DIVIDE", "/");
    return '/';
}

"\\" {
    update_loc();
    record_tok("INTDIV", "\\");
    return '\\';
}

"^" {
    update_loc();
    record_tok("POWER", "^");
    return '^';
}

"<>" {
    update_loc();
    record_tok("NOT_EQUALS", "<>");
    return TOKEN_NEQ;
}

"<=" {
    update_loc();
    record_tok("LESS_EQUALS", "<=");
    return TOKEN_LE;
}

">=" {
    update_loc();
    record_tok("GREATER_EQUALS", ">=");
    return TOKEN_GE;
}

"<" {
    update_loc();
    record_tok("LESS_THAN", "<");
    return TOKEN_LT;
}

">" {
    update_loc();
    record_tok("GREATER_THAN", ">");
    return TOKEN_GT;
}

"=" {
    update_loc();
    record_tok("EQUALS", "=");
    return TOKEN_EQ;
}

"END"[ \t]+"IF"|"ENDIF" {
    update_loc();
    record_tok("KEYWORD_END_IF", yytext);
    return TOKEN_END_IF;
}

"ELSE"[ \t]+"IF"|"ELSEIF" {
    update_loc();
    record_tok("KEYWORD_ELSEIF", yytext);
    return TOKEN_ELSEIF;
}

"LET" {
    update_loc();
    record_tok("KEYWORD_LET", yytext);
    return TOKEN_LET;
}

"PRINT"|"?" {
    update_loc();
    record_tok("KEYWORD_PRINT", yytext);
    return TOKEN_PRINT;
}

"INPUT" {
    update_loc();
    record_tok("KEYWORD_INPUT", yytext);
    return TOKEN_INPUT;
}

"IF" {
    update_loc();
    record_tok("KEYWORD_IF", yytext);
    return TOKEN_IF;
}

"THEN" {
    update_loc();
    record_tok("KEYWORD_THEN", yytext);
    return TOKEN_THEN;
}

"ELSE" {
    update_loc();
    record_tok("KEYWORD_ELSE", yytext);
    return TOKEN_ELSE;
}

"FOR" {
    update_loc();
    record_tok("KEYWORD_FOR", yytext);
    return TOKEN_FOR;
}

"TO" {
    update_loc();
    record_tok("KEYWORD_TO", yytext);
    return TOKEN_TO;
}

"STEP" {
    update_loc();
    record_tok("KEYWORD_STEP", yytext);
    return TOKEN_STEP;
}

"NEXT" {
    update_loc();
    record_tok("KEYWORD_NEXT", yytext);
    return TOKEN_NEXT;
}

"WHILE" {
    update_loc();
    record_tok("KEYWORD_WHILE", yytext);
    return TOKEN_WHILE;
}

"WEND" {
    update_loc();
    record_tok("KEYWORD_WEND", yytext);
    return TOKEN_WEND;
}

"GOTO" {
    update_loc();
    record_tok("KEYWORD_GOTO", yytext);
    return TOKEN_GOTO;
}

"GOSUB" {
    update_loc();
    record_tok("KEYWORD_GOSUB", yytext);
    return TOKEN_GOSUB;
}

"RETURN" {
    update_loc();
    record_tok("KEYWORD_RETURN", yytext);
    return TOKEN_RETURN;
}

"END" {
    update_loc();
    record_tok("KEYWORD_END", yytext);
    return TOKEN_END;
}

"STOP" {
    update_loc();
    record_tok("KEYWORD_STOP", yytext);
    return TOKEN_STOP;
}

"AND" {
    update_loc();
    record_tok("KEYWORD_AND", yytext);
    return TOKEN_AND;
}

"OR" {
    update_loc();
    record_tok("KEYWORD_OR", yytext);
    return TOKEN_OR;
}

"NOT" {
    update_loc();
    record_tok("KEYWORD_NOT", yytext);
    return TOKEN_NOT;
}

"MOD" {
    update_loc();
    record_tok("KEYWORD_MOD", yytext);
    return TOKEN_MOD;
}

"REM"([ \t][^\r\n]*)? {
    update_loc();
    record_tok("COMMENT", yytext);
}

"'"[^\r\n]* {
    update_loc();
    record_tok("COMMENT", yytext);
}

{INT} {
    update_loc();
    record_tok("INT_LITERAL", yytext);
    double val = atof(yytext);
    yylval.node = create_num_literal_node(val, yytext, false, current_token_loc);
    return TOKEN_INT_LITERAL;
}

{FLOAT} {
    update_loc();
    record_tok("FLOAT_LITERAL", yytext);
    double val = atof(yytext);
    yylval.node = create_num_literal_node(val, yytext, true, current_token_loc);
    return TOKEN_FLOAT_LITERAL;
}

\"([^"\\\r\n]|\\.)*\" {
    update_loc();
    record_tok("STRING_LITERAL", yytext);
    yylval.str_val = unescape_basic_string(yytext, yyleng);
    return TOKEN_STRING_LITERAL;
}

\"([^"\\\r\n]|\\.)* {
    update_loc();
    g_lexical_error_count++;
    const char *snip = get_source_line_snippet(current_token_loc.line);
    if (g_diagnostic_list) {
        diagnostic_list_append(g_diagnostic_list, "LEXICAL_ERROR", "Unterminated string literal", current_token_loc.line, current_token_loc.column, snip);
    }
}

{IDENT} {
    update_loc();
    record_tok("IDENTIFIER", yytext);
    yylval.str_val = safe_strdup(yytext);
    return TOKEN_IDENTIFIER;
}

<<EOF>> {
    if (!last_was_eol && !eof_emitted) {
        eof_emitted = 1;
        last_was_eol = 1;
        record_tok("EOL", "\\n");
        return TOKEN_EOL;
    }
    eof_emitted = 0;
    last_was_eol = 1;
    yyterminate();
}

. {
    update_loc();
    g_lexical_error_count++;
    char msg[128];
    snprintf(msg, sizeof(msg), "Invalid character '%c' (ASCII %d)", yytext[0], (unsigned char)yytext[0]);
    const char *snip = get_source_line_snippet(current_token_loc.line);
    if (g_diagnostic_list) {
        diagnostic_list_append(g_diagnostic_list, "LEXICAL_ERROR", msg, current_token_loc.line, current_token_loc.column, snip);
    }
}

%%
