#ifndef AST_H
#define AST_H

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

/* Source Location Information */
typedef struct SourceLocation {
    int line;
    int column;
} SourceLocation;

/* AST Node Types */
typedef enum {
    NODE_PROGRAM,
    NODE_STMT_LIST,
    NODE_ASSIGNMENT,
    NODE_PRINT,
    NODE_PRINT_ITEM,
    NODE_INPUT,
    NODE_IF,
    NODE_FOR,
    NODE_WHILE,
    NODE_GOTO,
    NODE_GOSUB,
    NODE_RETURN,
    NODE_END,
    NODE_STOP,
    NODE_LABELED_STMT,
    NODE_BINARY_EXPR,
    NODE_UNARY_EXPR,
    NODE_VAR,
    NODE_NUM_LITERAL,
    NODE_STRING_LITERAL
} ASTNodeType;

/* AST Node Forward Declaration */
typedef struct ASTNode ASTNode;

/* Dynamic Array of ASTNode pointers */
typedef struct ASTNodeList {
    ASTNode **items;
    size_t count;
    size_t capacity;
} ASTNodeList;

/* Generic AST Node Structure */
struct ASTNode {
    ASTNodeType type;
    SourceLocation location;

    union {
        /* NODE_PROGRAM or NODE_STMT_LIST */
        struct {
            ASTNodeList *statements;
        } program;

        /* NODE_LABELED_STMT */
        struct {
            int line_number;
            ASTNode *statement;
        } labeled_stmt;

        /* NODE_ASSIGNMENT */
        struct {
            char *var_name;
            ASTNode *value;
            bool has_let;
        } assignment;

        /* NODE_PRINT */
        struct {
            ASTNodeList *items;
            bool trailing_newline; /* false if ended with ; or , */
        } print_stmt;

        /* NODE_PRINT_ITEM */
        struct {
            ASTNode *expr;
            char *separator; /* ";", ",", or "" */
        } print_item;

        /* NODE_INPUT */
        struct {
            char *prompt;        /* optional prompt string, or NULL */
            char *separator;     /* ";" or "," if prompt exists */
            ASTNodeList *vars;   /* list of AST_VAR nodes */
        } input_stmt;

        /* NODE_IF */
        struct {
            ASTNode *condition;
            ASTNode *then_branch; /* NODE_STMT_LIST */
            ASTNode *else_branch; /* NODE_STMT_LIST or nested NODE_IF */
            bool is_single_line;
        } if_stmt;

        /* NODE_FOR */
        struct {
            char *var_name;
            ASTNode *start_expr;
            ASTNode *end_expr;
            ASTNode *step_expr;   /* optional, NULL if omitted */
            ASTNode *body;        /* NODE_STMT_LIST */
            char *next_var;       /* optional identifier after NEXT */
        } for_stmt;

        /* NODE_WHILE */
        struct {
            ASTNode *condition;
            ASTNode *body;        /* NODE_STMT_LIST */
        } while_stmt;

        /* NODE_GOTO */
        struct {
            int target_line;
            char *target_label;
        } goto_stmt;

        /* NODE_GOSUB */
        struct {
            int target_line;
            char *target_label;
        } gosub_stmt;

        /* NODE_BINARY_EXPR */
        struct {
            char *op;
            ASTNode *left;
            ASTNode *right;
        } binary_expr;

        /* NODE_UNARY_EXPR */
        struct {
            char *op;
            ASTNode *operand;
        } unary_expr;

        /* NODE_VAR */
        struct {
            char *name;
        } variable;

        /* NODE_NUM_LITERAL */
        struct {
            double value;
            char *raw_text;
            bool is_float;
        } num_literal;

        /* NODE_STRING_LITERAL */
        struct {
            char *value;
        } string_literal;
    } data;
};

/* Token record for lexical analysis stream */
typedef struct TokenRecord {
    char *type;
    char *lexeme;
    int line;
    int column;
} TokenRecord;

typedef struct TokenList {
    TokenRecord *items;
    size_t count;
    size_t capacity;
} TokenList;

/* Diagnostic record */
typedef struct Diagnostic {
    char *type;    /* "LEXICAL_ERROR", "SYNTAX_ERROR" */
    char *message;
    int line;
    int column;
    char *snippet;
} Diagnostic;

typedef struct DiagnosticList {
    Diagnostic *items;
    size_t count;
    size_t capacity;
} DiagnosticList;

/* AST Node List Helpers */
ASTNodeList *ast_node_list_create(void);
void ast_node_list_append(ASTNodeList *list, ASTNode *node);
void ast_node_list_free(ASTNodeList *list);

/* Node Constructors */
ASTNode *create_program_node(ASTNodeList *statements, SourceLocation loc);
ASTNode *create_stmt_list_node(ASTNodeList *statements, SourceLocation loc);
ASTNode *create_labeled_stmt_node(int line_number, ASTNode *stmt, SourceLocation loc);
ASTNode *create_assignment_node(char *var_name, ASTNode *value, bool has_let, SourceLocation loc);
ASTNode *create_print_node(ASTNodeList *items, bool trailing_newline, SourceLocation loc);
ASTNode *create_print_item_node(ASTNode *expr, const char *separator, SourceLocation loc);
ASTNode *create_input_node(char *prompt, const char *separator, ASTNodeList *vars, SourceLocation loc);
ASTNode *create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch, bool is_single_line, SourceLocation loc);
ASTNode *create_for_node(char *var_name, ASTNode *start_expr, ASTNode *end_expr, ASTNode *step_expr, ASTNode *body, char *next_var, SourceLocation loc);
ASTNode *create_while_node(ASTNode *condition, ASTNode *body, SourceLocation loc);
ASTNode *create_goto_node(int target_line, const char *target_label, SourceLocation loc);
ASTNode *create_gosub_node(int target_line, const char *target_label, SourceLocation loc);
ASTNode *create_return_node(SourceLocation loc);
ASTNode *create_end_node(SourceLocation loc);
ASTNode *create_stop_node(SourceLocation loc);
ASTNode *create_binary_expr_node(const char *op, ASTNode *left, ASTNode *right, SourceLocation loc);
ASTNode *create_unary_expr_node(const char *op, ASTNode *operand, SourceLocation loc);
ASTNode *create_var_node(const char *name, SourceLocation loc);
ASTNode *create_num_literal_node(double val, const char *raw_text, bool is_float, SourceLocation loc);
ASTNode *create_string_literal_node(const char *value, SourceLocation loc);

/* AST Cleanup */
void free_ast(ASTNode *node);

/* JSON Output Helpers */
void print_ast_json(FILE *out, const ASTNode *node, int indent);
char *json_escape_string(const char *input);
char *safe_strdup(const char *s);

/* Token and Diagnostic List Helpers */
TokenList *token_list_create(void);
void token_list_append(TokenList *list, const char *type, const char *lexeme, int line, int column);
void token_list_free(TokenList *list);

DiagnosticList *diagnostic_list_create(void);
void diagnostic_list_append(DiagnosticList *list, const char *type, const char *message, int line, int column, const char *snippet);
void diagnostic_list_free(DiagnosticList *list);

#endif /* AST_H */

