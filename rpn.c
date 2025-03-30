#include "rpn.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "utils.h"

int eval_functions(const char* token, num_stack* s, int* is_error, double x) {
    int res = 1;
    if (strcmp(token, "x") == 0) {
        num_stack_push(s, x);
    } else if (strcmp(token, "sin") == 0) {
        num_stack_push(s, sin(num_stack_pop(s)));
    } else if (strcmp(token, "cos") == 0) {
        num_stack_push(s, cos(num_stack_pop(s)));
    } else if (strcmp(token, "tan") == 0) {
        double val = num_stack_pop(s);
        if (fabs(cos(val)) < 1e-10)
            *is_error = 1;
        else
            num_stack_push(s, tan(val));
    } else if (strcmp(token, "ctg") == 0) {
        double val = num_stack_pop(s);
        if (fabs(sin(val)) < 1e-10)
            *is_error = 1;
        else
            num_stack_push(s, 1.0 / tan(val));
    } else if (strcmp(token, "sqrt") == 0) {
        double val = num_stack_pop(s);
        if (val < 0)
            *is_error = 1;
        else
            num_stack_push(s, sqrt(val));
    } else if (strcmp(token, "ln") == 0) {
        double val = num_stack_pop(s);
        if (val <= 0)
            *is_error = 1;
        else
            num_stack_push(s, log(val));
    } else if (strcmp(token, "u-") == 0) {
        num_stack_push(s, -num_stack_pop(s));
    } else {
        res = 0;
    }
    return res;
}
int eval_num(const char* token, num_stack* s) {
    int res = 1;
    if (is_digit(token[0]) || token[0] == '.') {
        num_stack_push(s, atof(token));
    } else {
        res = 0;
    }
    return res;
}
void eval_operation(const char* token, num_stack* s, int* is_error) {
    double b = num_stack_pop(s);
    double a = num_stack_pop(s);

    switch (token[0]) {
        case '+':
            num_stack_push(s, a + b);
            break;
        case '-':
            num_stack_push(s, a - b);
            break;
        case '*':
            num_stack_push(s, a * b);
            break;
        case '/':

            if (fabs(b) < 1e-10)
                *is_error = 1;
            else
                num_stack_push(s, a / b);
            break;
        case '^':

            if (a < 0 && floor(b) != b)
                *is_error = 1;
            else if (a == 0 && b < 0)
                *is_error = 1;
            else
                num_stack_push(s, pow(a, b));
            break;
        default:
            *is_error = 1;
    }
}

double evaluate_rpn(const char* rpn, double x) {
    num_stack s;
    num_stack_init(&s);
    int is_error = 0;
    char token[MAX_SIZE];
    int token_len = 0;

    for (int i = 0; rpn[i] != '\0'; i++) {
        if (is_space(rpn[i]) && !is_error) {
            if (token_len > 0) {
                token[token_len] = '\0';
                int eval_num_res = eval_num(token, &s);
                int eval_func_res = 0;
                if (!eval_num_res) {
                    eval_func_res = eval_functions(token, &s, &is_error, x);
                }
                if (!eval_num_res && !eval_func_res) {
                    eval_operation(token, &s, &is_error);
                }
                token_len = 0;
            }
        } else if (!is_error) {
            token[token_len++] = rpn[i];
        }
    }
    double result = NAN;
    if (!is_error && num_stack_is_empty(&s)) {
        is_error = 1;
    }

    result = num_stack_pop(&s);

    if (!is_error && !num_stack_is_empty(&s)) {
        is_error = 1;
    }

    num_stack_free(&s);

    result = is_error ? NAN : result;

    return result;
}