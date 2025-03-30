#include "parser.h"

#include <stdlib.h>
#include <string.h>

#include "utils.h"

int get_precedence(const char* op) {
    if (strcmp(op, "sin") == 0 || strcmp(op, "cos") == 0 || strcmp(op, "tan") == 0 ||
        strcmp(op, "ctg") == 0 || strcmp(op, "sqrt") == 0 || strcmp(op, "ln") == 0)
        return 5;
    if (strcmp(op, "u-") == 0) return 4;
    if (strcmp(op, "^") == 0) return 3;
    if (strcmp(op, "*") == 0 || strcmp(op, "/") == 0) return 2;
    if (strcmp(op, "+") == 0 || strcmp(op, "-") == 0) return 1;
    return 0;
}

int is_function(const char* str) {
    return strcmp(str, "sin") == 0 || strcmp(str, "cos") == 0 || strcmp(str, "tan") == 0 ||
           strcmp(str, "ctg") == 0 || strcmp(str, "sqrt") == 0 || strcmp(str, "ln") == 0;
}

void process_alpha(int* token_len, const char* infix, char* rpn, char* token, int* i, int* unary, stack* s,
                   int* j) {
    *token_len = 0;
    while (is_alpha(infix[*i])) token[(*token_len)++] = infix[(*i)++];
    token[*token_len] = '\0';
    (*i)--;

    if (is_function(token)) {
        char* func_copy = strdup(token);
        stack_push(s, func_copy);
        free(func_copy);
        *unary = 1;
    } else {
        strcpy(rpn + *j, token);
        *j += *token_len;
        rpn[(*j)++] = ' ';
        *unary = 0;
    }
}

void process_parenthesis(const char* infix, int i, stack* s, char* rpn, int* unary, int* j) {
    if (infix[i] == '(') {
        char* temp = strdup("(");
        stack_push(s, temp);
        free(temp);
        *unary = 1;
    } else if (infix[i] == ')') {
        while (!stack_is_empty(s) && strcmp(stack_peek(s), "(") != 0) {
            char* popped = stack_pop(s);
            strcpy(rpn + *j, popped);
            *j += strlen(popped);
            rpn[(*j)++] = ' ';
            free(popped);
        }

        char* popped = stack_pop(s);
        free(popped);

        if (!stack_is_empty(s) && is_function(stack_peek(s))) {
            char* func = stack_pop(s);
            strcpy(rpn + *j, func);
            *j += strlen(func);
            rpn[(*j)++] = ' ';
            free(func);
        }
        *unary = 0;
    }
}

void process_digits(int* token_len, const char* infix, char* rpn, char* token, int* i, int* unary, int* j) {
    *token_len = 0;
    while (is_digit(infix[*i]) || infix[*i] == '.') token[(*token_len)++] = infix[(*i)++];
    token[*token_len] = '\0';
    (*i)--;

    strcpy(rpn + *j, token);
    *j += *token_len;
    rpn[(*j)++] = ' ';
    *unary = 0;
}

void infix_to_rpn(const char* infix, char* rpn) {
    stack s;
    stack_init(&s);
    char token[MAX_SIZE];
    int token_len = 0;
    int j = 0;
    int unary = 1;

    for (int i = 0; infix[i] != '\0'; i++) {
        if (!is_space(infix[i])) {
            if (is_alpha(infix[i])) {
                process_alpha(&token_len, infix, rpn, token, &i, &unary, &s, &j);
            } else if (is_digit(infix[i]) || infix[i] == '.') {
                process_digits(&token_len, infix, rpn, token, &i, &unary, &j);
            } else if (infix[i] == '(' || infix[i] == ')') {
                process_parenthesis(infix, i, &s, rpn, &unary, &j);
            } else {
                if (infix[i] == '-' && unary) {
                    char* u_minus = strdup("u-");
                    stack_push(&s, u_minus);
                    free(u_minus);
                } else {
                    char op[2] = {infix[i], '\0'};
                    char* op_copy = strdup(op);
                    while (!stack_is_empty(&s) && get_precedence(stack_peek(&s)) >= get_precedence(op_copy) &&
                           strcmp(stack_peek(&s), "(") != 0) {
                        char* popped = stack_pop(&s);
                        strcpy(rpn + j, popped);
                        j += strlen(popped);
                        rpn[j++] = ' ';
                        free(popped);
                    }
                    stack_push(&s, op_copy);
                    free(op_copy);
                    unary = 1;
                }
            }
        }
    }

    while (!stack_is_empty(&s)) {
        char* popped = stack_pop(&s);
        strcpy(rpn + j, popped);
        j += strlen(popped);
        rpn[j++] = ' ';
        free(popped);
    }

    rpn[j] = '\0';
    stack_free(&s);
}