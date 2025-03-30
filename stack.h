#ifndef CALCULATOR_STACK_H_
#define CALCULATOR_STACK_H_


typedef struct stack_node {
  char* data;
  struct stack_node* next;
} stack_node;

typedef struct {
  stack_node* top;
} stack;

typedef struct num_stack_node {
  double data;
  struct num_stack_node* next;
} num_stack_node;

typedef struct num_stack {
  num_stack_node* top;
} num_stack;


void stack_init(stack* s);
int stack_is_empty(const stack* s);
void stack_push(stack* s, const char* str);
char* stack_pop(stack* s);
const char* stack_peek(const stack* s);
void stack_free(stack* s);


void num_stack_init(num_stack* s);
int num_stack_is_empty(const num_stack* s);
void num_stack_push(num_stack* s, double num);
double num_stack_pop(num_stack* s);
void num_stack_free(num_stack* s);

#endif  