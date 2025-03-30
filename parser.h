#ifndef CALCULATOR_PARSER_H_
#define CALCULATOR_PARSER_H_
#include "stack.h"

int get_precedence(const char* op);
int is_function(const char* str);
void process_digits(int* token_len, const char* infix, char* rpn, char* token, int* i, int* unary, int* j);
void process_parenthesis(const char* infix, int i, stack* s, char* rpn, int* unary, int* j);
void process_alpha(int* token_len, const char* infix, char* rpn, char* token, int* i, int* unary, stack* s,
                   int* j);
void infix_to_rpn(const char* infix, char* rpn);

#endif  // CALCULATOR_PARSER_H_