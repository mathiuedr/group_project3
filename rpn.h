#ifndef CALCULATOR_RPN_H_
#define CALCULATOR_RPN_H_
#include "stack.h"

int eval_functions(const char* token, num_stack* s, int* is_error, double x);
void eval_operation(const char* token, num_stack* s, int* is_error);
int eval_num(const char* token, num_stack* s);
double evaluate_rpn(const char* rpn, double x);

#endif  // CALCULATOR_RPN_H_