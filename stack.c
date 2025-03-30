#include "stack.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void stack_init(stack* s) {
    if (s != NULL) s->top = NULL;
}

int stack_is_empty(const stack* s) { return s == NULL || s->top == NULL; }

void stack_push(stack* s, const char* str) {
    stack_node* new_node = (stack_node*)malloc(sizeof(stack_node));
    new_node->data = strdup(str);
    new_node->next = s->top;
    s->top = new_node;
}

char* stack_pop(stack* s) {
    char* result = NULL;
    if (!stack_is_empty(s)) {
        stack_node* temp = s->top;
        result = temp->data;
        s->top = temp->next;
        free(temp);
    }
    return result;
}

const char* stack_peek(const stack* s) { return stack_is_empty(s) ? NULL : s->top->data; }

void stack_free(stack* s) {
    if (s != NULL) {
        while (!stack_is_empty(s)) {
            char* data = stack_pop(s);
            free(data);
        }
    }
}

void num_stack_init(num_stack* s) {
    if (s != NULL) s->top = NULL;
}

int num_stack_is_empty(const num_stack* s) { return s == NULL || s->top == NULL; }

void num_stack_push(num_stack* s, double num) {
    num_stack_node* new_node = (num_stack_node*)malloc(sizeof(num_stack_node));
    new_node->data = num;
    new_node->next = s->top;
    s->top = new_node;
}

double num_stack_pop(num_stack* s) {
    num_stack_node* temp = s->top;
    double result = temp->data;
    s->top = temp->next;
    free(temp);
    return result;
}

void num_stack_free(num_stack* s) {
    if (s != NULL) {
        while (!num_stack_is_empty(s)) {
            num_stack_pop(s);
        }
    }
}