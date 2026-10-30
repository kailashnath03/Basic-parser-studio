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
#include <stdbool.h>
#include "ast.h"

extern int yylex(void);
extern int yylineno;
extern char *yytext;
extern FILE *yyin;

void yyerror(const char *s);

/* Globals populated during parsing */
ASTNode *g_root_ast = NULL;
TokenList *g_token_list = NULL;
DiagnosticList *g_diagnostic_list = NULL;
int g_syntax_error_count = 0;
int g_lexical_error_count = 0;
char **g_source_lines = NULL;
int g_source_line_count = 0;

const char *get_source_line_snippet(int line);

static SourceLocation make_loc(int line, int col) {
    SourceLocation loc;
    loc.line = line;
    loc.column = col;
    return loc;
}

extern SourceLocation current_token_loc;

%}

%code requires {
    #include "ast.h"
}

%union {
    int int_val;
    double float_val;
    char *str_val;
    ASTNode *node;
    ASTNodeList *node_list;
}

/* Tokens */
%token <str_val> TOKEN_IDENTIFIER
%token <node> TOKEN_INT_LITERAL
%token <node> TOKEN_FLOAT_LITERAL
%token <str_val> TOKEN_STRING_LITERAL

/* Keywords */
%token TOKEN_LET
%token TOKEN_PRINT
%token TOKEN_INPUT
%token TOKEN_IF
%token TOKEN_THEN
%token TOKEN_ELSE
%token TOKEN_ELSEIF
%token TOKEN_END_IF
%token TOKEN_FOR
%token TOKEN_TO
%token TOKEN_STEP
%token TOKEN_NEXT
%token TOKEN_WHILE
%token TOKEN_WEND
%token TOKEN_GOTO
%token TOKEN_GOSUB
%token TOKEN_RETURN
%token TOKEN_END
%token TOKEN_STOP

/* Delimiters */
%token TOKEN_EOL
%token TOKEN_COLON

/* Logical and Relational Operators */
%token TOKEN_AND
%token TOKEN_OR
%token TOKEN_NOT
%token TOKEN_EQ
%token TOKEN_NEQ
%token TOKEN_LE
%token TOKEN_GE
%token TOKEN_LT
%token TOKEN_GT
%token TOKEN_MOD

/* Nonterminal types */
%type <node> program statement assignment_stmt print_stmt input_stmt
%type <node> if_stmt for_stmt while_stmt goto_stmt gosub_stmt return_stmt end_stmt stop_stmt
%type <node> expression primary_expr print_item opt_else_clause
%type <node_list> lines line statements_on_line block_lines
%type <node_list> print_item_list print_item_list_opt var_list
%type <str_val> opt_next_var
%type <node> opt_step
%type <int_val> opt_line_label

/* Operator Precedence and Associativity */
%precedence THEN_PREC
%precedence TOKEN_ELSE

%left TOKEN_OR
%left TOKEN_AND
%precedence TOKEN_NOT
%nonassoc TOKEN_EQ TOKEN_NEQ TOKEN_LT TOKEN_GT TOKEN_LE TOKEN_GE
%left '+' '-'
%left '*' '/' '\\' TOKEN_MOD
%precedence UMINUS UPLUS
%right '^'

%start program

%%

program
    : lines {
        SourceLocation loc = make_loc(1, 1);
        g_root_ast = create_program_node($1, loc);
        $$ = g_root_ast;
    }
    ;

lines
    : %empty {
        $$ = ast_node_list_create();
    }
    | lines line {
        $$ = $1;
        if ($2) {
            for (size_t i = 0; i < $2->count; i++) {
                ast_node_list_append($$, $2->items[i]);
            }
            free($2->items);
            free($2);
        }
    }
    ;

line
    : TOKEN_EOL {
        $$ = NULL;
    }
    | opt_line_label statements_on_line TOKEN_EOL {
        $$ = $2;
        if ($1 > 0 && $$ && $$->count > 0) {
            /* Attach line number to the first statement on this line */
            SourceLocation loc = make_loc($$->items[0]->location.line, 1);
            $$->items[0] = create_labeled_stmt_node($1, $$->items[0], loc);
        }
    }
    ;

opt_line_label
    : %empty {
        $$ = 0;
    }
    | TOKEN_INT_LITERAL {
        $$ = (int)$1->data.num_literal.value;
        free_ast($1);
    }
    ;

statements_on_line
    : statement {
        $$ = ast_node_list_create();
        if ($1) ast_node_list_append($$, $1);
    }
    | statements_on_line TOKEN_COLON statement {
        $$ = $1;
        if ($3) ast_node_list_append($$, $3);
    }
    ;

block_lines
    : %empty {
        $$ = ast_node_list_create();
    }
    | block_lines line {
        $$ = $1;
        if ($2) {
            for (size_t i = 0; i < $2->count; i++) {
                ast_node_list_append($$, $2->items[i]);
            }
            free($2->items);
            free($2);
        }
    }
    ;

statement
    : assignment_stmt { $$ = $1; }
    | print_stmt      { $$ = $1; }
    | input_stmt      { $$ = $1; }
    | if_stmt         { $$ = $1; }
    | for_stmt        { $$ = $1; }
    | while_stmt      { $$ = $1; }
    | goto_stmt       { $$ = $1; }
    | gosub_stmt      { $$ = $1; }
    | return_stmt     { $$ = $1; }
    | end_stmt        { $$ = $1; }
    | stop_stmt       { $$ = $1; }
    ;

/* Assignment Statement */
assignment_stmt
    : TOKEN_LET TOKEN_IDENTIFIER TOKEN_EQ expression {
        SourceLocation loc = $4 ? $4->location : make_loc(yylineno, 1);
        $$ = create_assignment_node($2, $4, true, loc);
        free($2);
    }
    | TOKEN_IDENTIFIER TOKEN_EQ expression {
        SourceLocation loc = $3 ? $3->location : make_loc(yylineno, 1);
        $$ = create_assignment_node($1, $3, false, loc);
        free($1);
    }
    ;

/* Print Statement */
print_stmt
    : TOKEN_PRINT print_item_list_opt {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_print_node($2, true, loc);
    }
    | TOKEN_PRINT print_item_list ',' {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_print_node($2, false, loc);
    }
    | TOKEN_PRINT print_item_list ';' {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_print_node($2, false, loc);
    }
    ;

print_item_list_opt
    : %empty {
        $$ = ast_node_list_create();
    }
    | print_item_list {
        $$ = $1;
    }
    ;

print_item_list
    : print_item {
        $$ = ast_node_list_create();
        if ($1) ast_node_list_append($$, $1);
    }
    | print_item_list ',' print_item {
        $$ = $1;
        if ($3) ast_node_list_append($$, $3);
    }
    | print_item_list ';' print_item {
        $$ = $1;
        if ($3) ast_node_list_append($$, $3);
    }
    ;

print_item
    : expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_print_item_node($1, "", loc);
    }
    ;

/* Input Statement */
input_stmt
    : TOKEN_INPUT var_list {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_input_node(NULL, NULL, $2, loc);
    }
    | TOKEN_INPUT TOKEN_STRING_LITERAL ';' var_list {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_input_node($2, ";", $4, loc);
        free($2);
    }
    | TOKEN_INPUT TOKEN_STRING_LITERAL ',' var_list {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_input_node($2, ",", $4, loc);
        free($2);
    }
    ;

var_list
    : TOKEN_IDENTIFIER {
        $$ = ast_node_list_create();
        SourceLocation loc = make_loc(yylineno, 1);
        ast_node_list_append($$, create_var_node($1, loc));
        free($1);
    }
    | var_list ',' TOKEN_IDENTIFIER {
        $$ = $1;
        SourceLocation loc = make_loc(yylineno, 1);
        ast_node_list_append($$, create_var_node($3, loc));
        free($3);
    }
    ;

/* If Statement */
if_stmt
    /* Multiline IF ... THEN \n ... END IF */
    : TOKEN_IF expression TOKEN_THEN TOKEN_EOL block_lines opt_else_clause TOKEN_END_IF {
        SourceLocation loc = $2 ? $2->location : make_loc(yylineno, 1);
        ASTNode *then_branch = create_stmt_list_node($5, loc);
        $$ = create_if_node($2, then_branch, $6, false, loc);
    }
    /* Single-line IF ... THEN stmt */
    | TOKEN_IF expression TOKEN_THEN statement %prec THEN_PREC {
        SourceLocation loc = $2 ? $2->location : make_loc(yylineno, 1);
        ASTNodeList *then_list = ast_node_list_create();
        if ($4) ast_node_list_append(then_list, $4);
        ASTNode *then_branch = create_stmt_list_node(then_list, loc);
        $$ = create_if_node($2, then_branch, NULL, true, loc);
    }
    /* Single-line IF ... THEN stmt ELSE stmt */
    | TOKEN_IF expression TOKEN_THEN statement TOKEN_ELSE statement {
        SourceLocation loc = $2 ? $2->location : make_loc(yylineno, 1);
        ASTNodeList *then_list = ast_node_list_create();
        if ($4) ast_node_list_append(then_list, $4);
        ASTNode *then_branch = create_stmt_list_node(then_list, loc);

        ASTNodeList *else_list = ast_node_list_create();
        if ($6) ast_node_list_append(else_list, $6);
        ASTNode *else_branch = create_stmt_list_node(else_list, loc);

        $$ = create_if_node($2, then_branch, else_branch, true, loc);
    }
    ;

opt_else_clause
    : %empty {
        $$ = NULL;
    }
    | TOKEN_ELSE TOKEN_EOL block_lines {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_stmt_list_node($3, loc);
    }
    | TOKEN_ELSEIF expression TOKEN_THEN TOKEN_EOL block_lines opt_else_clause {
        SourceLocation loc = $2 ? $2->location : make_loc(yylineno, 1);
        ASTNode *then_branch = create_stmt_list_node($5, loc);
        $$ = create_if_node($2, then_branch, $6, false, loc);
    }
    ;

/* For Statement */
for_stmt
    : TOKEN_FOR TOKEN_IDENTIFIER TOKEN_EQ expression TOKEN_TO expression opt_step TOKEN_EOL block_lines TOKEN_NEXT opt_next_var {
        SourceLocation loc = make_loc(yylineno, 1);
        ASTNode *body_node = create_stmt_list_node($9, loc);
        $$ = create_for_node($2, $4, $6, $7, body_node, $11, loc);
        free($2);
        if ($11) free($11);
    }
    ;

opt_step
    : %empty {
        $$ = NULL;
    }
    | TOKEN_STEP expression {
        $$ = $2;
    }
    ;

opt_next_var
    : %empty {
        $$ = NULL;
    }
    | TOKEN_IDENTIFIER {
        $$ = $1;
    }
    ;

/* While Statement */
while_stmt
    : TOKEN_WHILE expression TOKEN_EOL block_lines TOKEN_WEND {
        SourceLocation loc = make_loc(yylineno, 1);
        ASTNode *body_node = create_stmt_list_node($4, loc);
        $$ = create_while_node($2, body_node, loc);
    }
    ;

/* Goto Statement */
goto_stmt
    : TOKEN_GOTO TOKEN_INT_LITERAL {
        SourceLocation loc = make_loc(yylineno, 1);
        int line_num = (int)$2->data.num_literal.value;
        char num_buf[32];
        snprintf(num_buf, sizeof(num_buf), "%d", line_num);
        $$ = create_goto_node(line_num, num_buf, loc);
        free_ast($2);
    }
    | TOKEN_GOTO TOKEN_IDENTIFIER {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_goto_node(0, $2, loc);
        free($2);
    }
    ;

/* Gosub Statement */
gosub_stmt
    : TOKEN_GOSUB TOKEN_INT_LITERAL {
        SourceLocation loc = make_loc(yylineno, 1);
        int line_num = (int)$2->data.num_literal.value;
        char num_buf[32];
        snprintf(num_buf, sizeof(num_buf), "%d", line_num);
        $$ = create_gosub_node(line_num, num_buf, loc);
        free_ast($2);
    }
    | TOKEN_GOSUB TOKEN_IDENTIFIER {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_gosub_node(0, $2, loc);
        free($2);
    }
    ;

/* Return Statement */
return_stmt
    : TOKEN_RETURN {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_return_node(loc);
    }
    ;

/* End Statement */
end_stmt
    : TOKEN_END {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_end_node(loc);
    }
    ;

/* Stop Statement */
stop_stmt
    : TOKEN_STOP {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_stop_node(loc);
    }
    ;

/* Expressions */
expression
    : primary_expr {
        $$ = $1;
    }
    | expression TOKEN_OR expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("OR", $1, $3, loc);
    }
    | expression TOKEN_AND expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("AND", $1, $3, loc);
    }
    | TOKEN_NOT expression {
        SourceLocation loc = $2 ? $2->location : make_loc(yylineno, 1);
        $$ = create_unary_expr_node("NOT", $2, loc);
    }
    | expression TOKEN_EQ expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("=", $1, $3, loc);
    }
    | expression TOKEN_NEQ expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("<>", $1, $3, loc);
    }
    | expression TOKEN_LT expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("<", $1, $3, loc);
    }
    | expression TOKEN_GT expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node(">", $1, $3, loc);
    }
    | expression TOKEN_LE expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("<=", $1, $3, loc);
    }
    | expression TOKEN_GE expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node(">=", $1, $3, loc);
    }
    | expression '+' expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("+", $1, $3, loc);
    }
    | expression '-' expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("-", $1, $3, loc);
    }
    | expression '*' expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("*", $1, $3, loc);
    }
    | expression '/' expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("/", $1, $3, loc);
    }
    | expression '\\' expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("\\", $1, $3, loc);
    }
    | expression TOKEN_MOD expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("MOD", $1, $3, loc);
    }
    | expression '^' expression {
        SourceLocation loc = $1 ? $1->location : make_loc(yylineno, 1);
        $$ = create_binary_expr_node("^", $1, $3, loc);
    }
    | '-' expression %prec UMINUS {
        SourceLocation loc = $2 ? $2->location : make_loc(yylineno, 1);
        $$ = create_unary_expr_node("-", $2, loc);
    }
    | '+' expression %prec UPLUS {
        SourceLocation loc = $2 ? $2->location : make_loc(yylineno, 1);
        $$ = create_unary_expr_node("+", $2, loc);
    }
    ;

primary_expr
    : TOKEN_INT_LITERAL {
        $$ = $1;
    }
    | TOKEN_FLOAT_LITERAL {
        $$ = $1;
    }
    | TOKEN_STRING_LITERAL {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_string_literal_node($1, loc);
        free($1);
    }
    | TOKEN_IDENTIFIER {
        SourceLocation loc = make_loc(yylineno, 1);
        $$ = create_var_node($1, loc);
        free($1);
    }
    | '(' expression ')' {
        $$ = $2;
    }
    ;

%%

const char *get_source_line_snippet(int line) {
    if (line >= 1 && line <= g_source_line_count && g_source_lines) {
        return g_source_lines[line - 1];
    }
    return "";
}

void yyerror(const char *s) {
    g_syntax_error_count++;
    int col = current_token_loc.column > 0 ? current_token_loc.column : 1;
    int line = current_token_loc.line > 0 ? current_token_loc.line : yylineno;
    const char *snippet = get_source_line_snippet(line);
    
    char clean_msg[256];
    if (strncmp(s, "syntax error", 12) == 0) {
        if (yytext && strlen(yytext) > 0 && yytext[0] != '\n') {
            snprintf(clean_msg, sizeof(clean_msg), "Syntax error near '%s'", yytext);
        } else {
            snprintf(clean_msg, sizeof(clean_msg), "Syntax error: unexpected end of statement or token");
        }
    } else {
        snprintf(clean_msg, sizeof(clean_msg), "%s", s);
    }

    if (g_diagnostic_list) {
        diagnostic_list_append(g_diagnostic_list, "SYNTAX_ERROR", clean_msg, line, col, snippet);
    }
}
