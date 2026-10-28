#include "ast.h"
#include <ctype.h>

static char *safe_strdup(const char *s) {
    if (!s) return NULL;
    size_t len = strlen(s);
    char *copy = (char *)malloc(len + 1);
    if (copy) {
        memcpy(copy, s, len + 1);
    }
    return copy;
}

char *json_escape_string(const char *input) {
    if (!input) return safe_strdup("");
    size_t len = strlen(input);
    /* Worst case: every char needs \u00XX (6 chars) */
    char *escaped = (char *)malloc(len * 6 + 1);
    if (!escaped) return safe_strdup("");

    size_t j = 0;
    for (size_t i = 0; i < len; i++) {
        unsigned char c = (unsigned char)input[i];
        switch (c) {
            case '\"': escaped[j++] = '\\'; escaped[j++] = '\"'; break;
            case '\\': escaped[j++] = '\\'; escaped[j++] = '\\'; break;
            case '\b': escaped[j++] = '\\'; escaped[j++] = 'b'; break;
            case '\f': escaped[j++] = '\\'; escaped[j++] = 'f'; break;
            case '\n': escaped[j++] = '\\'; escaped[j++] = 'n'; break;
            case '\r': escaped[j++] = '\\'; escaped[j++] = 'r'; break;
            case '\t': escaped[j++] = '\\'; escaped[j++] = 't'; break;
            default:
                if (c < 32) {
                    sprintf(&escaped[j], "\\u%04x", c);
                    j += 6;
                } else {
                    escaped[j++] = (char)c;
                }
                break;
        }
    }
    escaped[j] = '\0';
    return escaped;
}

ASTNodeList *ast_node_list_create(void) {
    ASTNodeList *list = (ASTNodeList *)calloc(1, sizeof(ASTNodeList));
    return list;
}

void ast_node_list_append(ASTNodeList *list, ASTNode *node) {
    if (!list || !node) return;
    if (list->count >= list->capacity) {
        size_t new_cap = list->capacity == 0 ? 8 : list->capacity * 2;
        ASTNode **new_items = (ASTNode **)realloc(list->items, new_cap * sizeof(ASTNode *));
        if (!new_items) return;
        list->items = new_items;
        list->capacity = new_cap;
    }
    list->items[list->count++] = node;
}

void ast_node_list_free(ASTNodeList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->count; i++) {
        free_ast(list->items[i]);
    }
    free(list->items);
    free(list);
}

static ASTNode *alloc_node(ASTNodeType type, SourceLocation loc) {
    ASTNode *n = (ASTNode *)calloc(1, sizeof(ASTNode));
    if (n) {
        n->type = type;
        n->location = loc;
    }
    return n;
}

ASTNode *create_program_node(ASTNodeList *statements, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_PROGRAM, loc);
    if (n) {
        n->data.program.statements = statements ? statements : ast_node_list_create();
    }
    return n;
}

ASTNode *create_stmt_list_node(ASTNodeList *statements, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_STMT_LIST, loc);
    if (n) {
        n->data.program.statements = statements ? statements : ast_node_list_create();
    }
    return n;
}

ASTNode *create_labeled_stmt_node(int line_number, ASTNode *stmt, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_LABELED_STMT, loc);
    if (n) {
        n->data.labeled_stmt.line_number = line_number;
        n->data.labeled_stmt.statement = stmt;
    }
    return n;
}

ASTNode *create_assignment_node(char *var_name, ASTNode *value, bool has_let, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_ASSIGNMENT, loc);
    if (n) {
        n->data.assignment.var_name = safe_strdup(var_name);
        n->data.assignment.value = value;
        n->data.assignment.has_let = has_let;
    }
    return n;
}

ASTNode *create_print_node(ASTNodeList *items, bool trailing_newline, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_PRINT, loc);
    if (n) {
        n->data.print_stmt.items = items ? items : ast_node_list_create();
        n->data.print_stmt.trailing_newline = trailing_newline;
    }
    return n;
}

ASTNode *create_print_item_node(ASTNode *expr, const char *separator, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_PRINT_ITEM, loc);
    if (n) {
        n->data.print_item.expr = expr;
        n->data.print_item.separator = safe_strdup(separator ? separator : "");
    }
    return n;
}

ASTNode *create_input_node(char *prompt, const char *separator, ASTNodeList *vars, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_INPUT, loc);
    if (n) {
        n->data.input_stmt.prompt = safe_strdup(prompt);
        n->data.input_stmt.separator = safe_strdup(separator ? separator : "");
        n->data.input_stmt.vars = vars ? vars : ast_node_list_create();
    }
    return n;
}

ASTNode *create_if_node(ASTNode *condition, ASTNode *then_branch, ASTNode *else_branch, bool is_single_line, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_IF, loc);
    if (n) {
        n->data.if_stmt.condition = condition;
        n->data.if_stmt.then_branch = then_branch;
        n->data.if_stmt.else_branch = else_branch;
        n->data.if_stmt.is_single_line = is_single_line;
    }
    return n;
}

ASTNode *create_for_node(char *var_name, ASTNode *start_expr, ASTNode *end_expr, ASTNode *step_expr, ASTNode *body, char *next_var, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_FOR, loc);
    if (n) {
        n->data.for_stmt.var_name = safe_strdup(var_name);
        n->data.for_stmt.start_expr = start_expr;
        n->data.for_stmt.end_expr = end_expr;
        n->data.for_stmt.step_expr = step_expr;
        n->data.for_stmt.body = body;
        n->data.for_stmt.next_var = safe_strdup(next_var);
    }
    return n;
}

ASTNode *create_while_node(ASTNode *condition, ASTNode *body, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_WHILE, loc);
    if (n) {
        n->data.while_stmt.condition = condition;
        n->data.while_stmt.body = body;
    }
    return n;
}

ASTNode *create_goto_node(int target_line, const char *target_label, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_GOTO, loc);
    if (n) {
        n->data.goto_stmt.target_line = target_line;
        n->data.goto_stmt.target_label = safe_strdup(target_label);
    }
    return n;
}

ASTNode *create_gosub_node(int target_line, const char *target_label, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_GOSUB, loc);
    if (n) {
        n->data.gosub_stmt.target_line = target_line;
        n->data.gosub_stmt.target_label = safe_strdup(target_label);
    }
    return n;
}

ASTNode *create_return_node(SourceLocation loc) {
    return alloc_node(NODE_RETURN, loc);
}

ASTNode *create_end_node(SourceLocation loc) {
    return alloc_node(NODE_END, loc);
}

ASTNode *create_stop_node(SourceLocation loc) {
    return alloc_node(NODE_STOP, loc);
}

ASTNode *create_binary_expr_node(const char *op, ASTNode *left, ASTNode *right, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_BINARY_EXPR, loc);
    if (n) {
        n->data.binary_expr.op = safe_strdup(op);
        n->data.binary_expr.left = left;
        n->data.binary_expr.right = right;
    }
    return n;
}

ASTNode *create_unary_expr_node(const char *op, ASTNode *operand, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_UNARY_EXPR, loc);
    if (n) {
        n->data.unary_expr.op = safe_strdup(op);
        n->data.unary_expr.operand = operand;
    }
    return n;
}

ASTNode *create_var_node(const char *name, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_VAR, loc);
    if (n) {
        n->data.variable.name = safe_strdup(name);
    }
    return n;
}

ASTNode *create_num_literal_node(double val, const char *raw_text, bool is_float, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_NUM_LITERAL, loc);
    if (n) {
        n->data.num_literal.value = val;
        n->data.num_literal.raw_text = safe_strdup(raw_text);
        n->data.num_literal.is_float = is_float;
    }
    return n;
}

ASTNode *create_string_literal_node(const char *value, SourceLocation loc) {
    ASTNode *n = alloc_node(NODE_STRING_LITERAL, loc);
    if (n) {
        n->data.string_literal.value = safe_strdup(value);
    }
    return n;
}

void free_ast(ASTNode *node) {
    if (!node) return;

    switch (node->type) {
        case NODE_PROGRAM:
        case NODE_STMT_LIST:
            ast_node_list_free(node->data.program.statements);
            break;
        case NODE_LABELED_STMT:
            free_ast(node->data.labeled_stmt.statement);
            break;
        case NODE_ASSIGNMENT:
            free(node->data.assignment.var_name);
            free_ast(node->data.assignment.value);
            break;
        case NODE_PRINT:
            ast_node_list_free(node->data.print_stmt.items);
            break;
        case NODE_PRINT_ITEM:
            free_ast(node->data.print_item.expr);
            free(node->data.print_item.separator);
            break;
        case NODE_INPUT:
            free(node->data.input_stmt.prompt);
            free(node->data.input_stmt.separator);
            ast_node_list_free(node->data.input_stmt.vars);
            break;
        case NODE_IF:
            free_ast(node->data.if_stmt.condition);
            free_ast(node->data.if_stmt.then_branch);
            free_ast(node->data.if_stmt.else_branch);
            break;
        case NODE_FOR:
            free(node->data.for_stmt.var_name);
            free_ast(node->data.for_stmt.start_expr);
            free_ast(node->data.for_stmt.end_expr);
            free_ast(node->data.for_stmt.step_expr);
            free_ast(node->data.for_stmt.body);
            free(node->data.for_stmt.next_var);
            break;
        case NODE_WHILE:
            free_ast(node->data.while_stmt.condition);
            free_ast(node->data.while_stmt.body);
            break;
        case NODE_GOTO:
            free(node->data.goto_stmt.target_label);
            break;
        case NODE_GOSUB:
            free(node->data.gosub_stmt.target_label);
            break;
        case NODE_BINARY_EXPR:
            free(node->data.binary_expr.op);
            free_ast(node->data.binary_expr.left);
            free_ast(node->data.binary_expr.right);
            break;
        case NODE_UNARY_EXPR:
            free(node->data.unary_expr.op);
            free_ast(node->data.unary_expr.operand);
            break;
        case NODE_VAR:
            free(node->data.variable.name);
            break;
        case NODE_NUM_LITERAL:
            free(node->data.num_literal.raw_text);
            break;
        case NODE_STRING_LITERAL:
            free(node->data.string_literal.value);
            break;
        case NODE_RETURN:
        case NODE_END:
        case NODE_STOP:
            break;
    }
    free(node);
}

static void print_indent(FILE *out, int indent) {
    for (int i = 0; i < indent; i++) {
        fputs("  ", out);
    }
}

void print_ast_json(FILE *out, const ASTNode *node, int indent) {
    if (!out) return;
    if (!node) {
        fputs("null", out);
        return;
    }

    print_indent(out, indent);
    fputs("{\n", out);

    print_indent(out, indent + 1);
    fputs("\"location\": { \"line\": ", out);
    fprintf(out, "%d, \"column\": %d },\n", node->location.line, node->location.column);

    switch (node->type) {
        case NODE_PROGRAM: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"Program\",\n", out);
            print_indent(out, indent + 1);
            fputs("\"statements\": [\n", out);
            ASTNodeList *list = node->data.program.statements;
            if (list) {
                for (size_t i = 0; i < list->count; i++) {
                    print_ast_json(out, list->items[i], indent + 2);
                    if (i + 1 < list->count) fputc(',', out);
                    fputc('\n', out);
                }
            }
            print_indent(out, indent + 1);
            fputs("]\n", out);
            break;
        }

        case NODE_STMT_LIST: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"StatementList\",\n", out);
            print_indent(out, indent + 1);
            fputs("\"statements\": [\n", out);
            ASTNodeList *list = node->data.program.statements;
            if (list) {
                for (size_t i = 0; i < list->count; i++) {
                    print_ast_json(out, list->items[i], indent + 2);
                    if (i + 1 < list->count) fputc(',', out);
                    fputc('\n', out);
                }
            }
            print_indent(out, indent + 1);
            fputs("]\n", out);
            break;
        }

        case NODE_LABELED_STMT: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"LabeledStatement\",\n", out);
            print_indent(out, indent + 1);
            fprintf(out, "\"lineNumber\": %d,\n", node->data.labeled_stmt.line_number);
            print_indent(out, indent + 1);
            fputs("\"statement\": \n", out);
            print_ast_json(out, node->data.labeled_stmt.statement, indent + 2);
            fputc('\n', out);
            break;
        }

        case NODE_ASSIGNMENT: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"AssignmentStatement\",\n", out);
            print_indent(out, indent + 1);
            char *esc_var = json_escape_string(node->data.assignment.var_name);
            fprintf(out, "\"variable\": \"%s\",\n", esc_var);
            free(esc_var);
            print_indent(out, indent + 1);
            fprintf(out, "\"hasLet\": %s,\n", node->data.assignment.has_let ? "true" : "false");
            print_indent(out, indent + 1);
            fputs("\"value\": \n", out);
            print_ast_json(out, node->data.assignment.value, indent + 2);
            fputc('\n', out);
            break;
        }

        case NODE_PRINT: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"PrintStatement\",\n", out);
            print_indent(out, indent + 1);
            fprintf(out, "\"trailingNewline\": %s,\n", node->data.print_stmt.trailing_newline ? "true" : "false");
            print_indent(out, indent + 1);
            fputs("\"items\": [\n", out);
            ASTNodeList *list = node->data.print_stmt.items;
            if (list) {
                for (size_t i = 0; i < list->count; i++) {
                    print_ast_json(out, list->items[i], indent + 2);
                    if (i + 1 < list->count) fputc(',', out);
                    fputc('\n', out);
                }
            }
            print_indent(out, indent + 1);
            fputs("]\n", out);
            break;
        }

        case NODE_PRINT_ITEM: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"PrintItem\",\n", out);
            print_indent(out, indent + 1);
            char *esc_sep = json_escape_string(node->data.print_item.separator);
            fprintf(out, "\"separator\": \"%s\",\n", esc_sep);
            free(esc_sep);
            print_indent(out, indent + 1);
            fputs("\"expression\": \n", out);
            print_ast_json(out, node->data.print_item.expr, indent + 2);
            fputc('\n', out);
            break;
        }

        case NODE_INPUT: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"InputStatement\",\n", out);
            print_indent(out, indent + 1);
            if (node->data.input_stmt.prompt) {
                char *esc_prompt = json_escape_string(node->data.input_stmt.prompt);
                fprintf(out, "\"prompt\": \"%s\",\n", esc_prompt);
                free(esc_prompt);
            } else {
                fputs("\"prompt\": null,\n", out);
            }
            print_indent(out, indent + 1);
            char *esc_sep = json_escape_string(node->data.input_stmt.separator);
            fprintf(out, "\"separator\": \"%s\",\n", esc_sep);
            free(esc_sep);
            print_indent(out, indent + 1);
            fputs("\"variables\": [\n", out);
            ASTNodeList *vars = node->data.input_stmt.vars;
            if (vars) {
                for (size_t i = 0; i < vars->count; i++) {
                    print_ast_json(out, vars->items[i], indent + 2);
                    if (i + 1 < vars->count) fputc(',', out);
                    fputc('\n', out);
                }
            }
            print_indent(out, indent + 1);
            fputs("]\n", out);
            break;
        }

        case NODE_IF: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"IfStatement\",\n", out);
            print_indent(out, indent + 1);
            fprintf(out, "\"isSingleLine\": %s,\n", node->data.if_stmt.is_single_line ? "true" : "false");
            print_indent(out, indent + 1);
            fputs("\"condition\": \n", out);
            print_ast_json(out, node->data.if_stmt.condition, indent + 2);
            fputs(",\n", out);

            print_indent(out, indent + 1);
            fputs("\"thenBranch\": \n", out);
            print_ast_json(out, node->data.if_stmt.then_branch, indent + 2);

            if (node->data.if_stmt.else_branch) {
                fputs(",\n", out);
                print_indent(out, indent + 1);
                fputs("\"elseBranch\": \n", out);
                print_ast_json(out, node->data.if_stmt.else_branch, indent + 2);
            }
            fputc('\n', out);
            break;
        }

        case NODE_FOR: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"ForStatement\",\n", out);
            print_indent(out, indent + 1);
            char *esc_var = json_escape_string(node->data.for_stmt.var_name);
            fprintf(out, "\"variable\": \"%s\",\n", esc_var);
            free(esc_var);

            print_indent(out, indent + 1);
            fputs("\"start\": \n", out);
            print_ast_json(out, node->data.for_stmt.start_expr, indent + 2);
            fputs(",\n", out);

            print_indent(out, indent + 1);
            fputs("\"end\": \n", out);
            print_ast_json(out, node->data.for_stmt.end_expr, indent + 2);

            if (node->data.for_stmt.step_expr) {
                fputs(",\n", out);
                print_indent(out, indent + 1);
                fputs("\"step\": \n", out);
                print_ast_json(out, node->data.for_stmt.step_expr, indent + 2);
            }

            fputs(",\n", out);
            print_indent(out, indent + 1);
            fputs("\"body\": \n", out);
            print_ast_json(out, node->data.for_stmt.body, indent + 2);

            if (node->data.for_stmt.next_var) {
                fputs(",\n", out);
                print_indent(out, indent + 1);
                char *esc_next = json_escape_string(node->data.for_stmt.next_var);
                fprintf(out, "\"nextVariable\": \"%s\"\n", esc_next);
                free(esc_next);
            } else {
                fputc('\n', out);
            }
            break;
        }

        case NODE_WHILE: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"WhileStatement\",\n", out);
            print_indent(out, indent + 1);
            fputs("\"condition\": \n", out);
            print_ast_json(out, node->data.while_stmt.condition, indent + 2);
            fputs(",\n", out);

            print_indent(out, indent + 1);
            fputs("\"body\": \n", out);
            print_ast_json(out, node->data.while_stmt.body, indent + 2);
            fputc('\n', out);
            break;
        }

        case NODE_GOTO: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"GotoStatement\",\n", out);
            print_indent(out, indent + 1);
            fprintf(out, "\"targetLine\": %d,\n", node->data.goto_stmt.target_line);
            print_indent(out, indent + 1);
            char *esc_label = json_escape_string(node->data.goto_stmt.target_label);
            fprintf(out, "\"targetLabel\": \"%s\"\n", esc_label);
            free(esc_label);
            break;
        }

        case NODE_GOSUB: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"GosubStatement\",\n", out);
            print_indent(out, indent + 1);
            fprintf(out, "\"targetLine\": %d,\n", node->data.gosub_stmt.target_line);
            print_indent(out, indent + 1);
            char *esc_label = json_escape_string(node->data.gosub_stmt.target_label);
            fprintf(out, "\"targetLabel\": \"%s\"\n", esc_label);
            free(esc_label);
            break;
        }

        case NODE_RETURN: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"ReturnStatement\"\n", out);
            break;
        }

        case NODE_END: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"EndStatement\"\n", out);
            break;
        }

        case NODE_STOP: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"StopStatement\"\n", out);
            break;
        }

        case NODE_BINARY_EXPR: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"BinaryExpression\",\n", out);
            print_indent(out, indent + 1);
            char *esc_op = json_escape_string(node->data.binary_expr.op);
            fprintf(out, "\"operator\": \"%s\",\n", esc_op);
            free(esc_op);

            print_indent(out, indent + 1);
            fputs("\"left\": \n", out);
            print_ast_json(out, node->data.binary_expr.left, indent + 2);
            fputs(",\n", out);

            print_indent(out, indent + 1);
            fputs("\"right\": \n", out);
            print_ast_json(out, node->data.binary_expr.right, indent + 2);
            fputc('\n', out);
            break;
        }

        case NODE_UNARY_EXPR: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"UnaryExpression\",\n", out);
            print_indent(out, indent + 1);
            char *esc_op = json_escape_string(node->data.unary_expr.op);
            fprintf(out, "\"operator\": \"%s\",\n", esc_op);
            free(esc_op);

            print_indent(out, indent + 1);
            fputs("\"operand\": \n", out);
            print_ast_json(out, node->data.unary_expr.operand, indent + 2);
            fputc('\n', out);
            break;
        }

        case NODE_VAR: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"Variable\",\n", out);
            print_indent(out, indent + 1);
            char *esc_name = json_escape_string(node->data.variable.name);
            fprintf(out, "\"name\": \"%s\"\n", esc_name);
            free(esc_name);
            break;
        }

        case NODE_NUM_LITERAL: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"NumberLiteral\",\n", out);
            print_indent(out, indent + 1);
            fprintf(out, "\"value\": %g,\n", node->data.num_literal.value);
            print_indent(out, indent + 1);
            char *esc_raw = json_escape_string(node->data.num_literal.raw_text);
            fprintf(out, "\"rawText\": \"%s\",\n", esc_raw);
            free(esc_raw);
            print_indent(out, indent + 1);
            fprintf(out, "\"isFloat\": %s\n", node->data.num_literal.is_float ? "true" : "false");
            break;
        }

        case NODE_STRING_LITERAL: {
            print_indent(out, indent + 1);
            fputs("\"type\": \"StringLiteral\",\n", out);
            print_indent(out, indent + 1);
            char *esc_val = json_escape_string(node->data.string_literal.value);
            fprintf(out, "\"value\": \"%s\"\n", esc_val);
            free(esc_val);
            break;
        }
    }

    print_indent(out, indent);
    fputs("}", out);
}

TokenList *token_list_create(void) {
    TokenList *list = (TokenList *)calloc(1, sizeof(TokenList));
    return list;
}

void token_list_append(TokenList *list, const char *type, const char *lexeme, int line, int column) {
    if (!list) return;
    if (list->count >= list->capacity) {
        size_t new_cap = list->capacity == 0 ? 32 : list->capacity * 2;
        TokenRecord *new_items = (TokenRecord *)realloc(list->items, new_cap * sizeof(TokenRecord));
        if (!new_items) return;
        list->items = new_items;
        list->capacity = new_cap;
    }
    list->items[list->count].type = safe_strdup(type);
    list->items[list->count].lexeme = safe_strdup(lexeme);
    list->items[list->count].line = line;
    list->items[list->count].column = column;
    list->count++;
}

void token_list_free(TokenList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i].type);
        free(list->items[i].lexeme);
    }
    free(list->items);
    free(list);
}

DiagnosticList *diagnostic_list_create(void) {
    DiagnosticList *list = (DiagnosticList *)calloc(1, sizeof(DiagnosticList));
    return list;
}

void diagnostic_list_append(DiagnosticList *list, const char *type, const char *message, int line, int column, const char *snippet) {
    if (!list) return;
    if (list->count >= list->capacity) {
        size_t new_cap = list->capacity == 0 ? 8 : list->capacity * 2;
        Diagnostic *new_items = (Diagnostic *)realloc(list->items, new_cap * sizeof(Diagnostic));
        if (!new_items) return;
        list->items = new_items;
        list->capacity = new_cap;
    }
    list->items[list->count].type = safe_strdup(type);
    list->items[list->count].message = safe_strdup(message);
    list->items[list->count].line = line;
    list->items[list->count].column = column;
    list->items[list->count].snippet = safe_strdup(snippet);
    list->count++;
}

void diagnostic_list_free(DiagnosticList *list) {
    if (!list) return;
    for (size_t i = 0; i < list->count; i++) {
        free(list->items[i].type);
        free(list->items[i].message);
        free(list->items[i].snippet);
    }
    free(list->items);
    free(list);
}

