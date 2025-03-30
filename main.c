#include <stdio.h>
#include "parser.h"
#include "graph.h"

#define MAX_SIZE 100
#define MAX_RPN_SIZE (MAX_SIZE * 2)

int main() {
    char infix[MAX_SIZE];
    char rpn[MAX_RPN_SIZE];
    fgets(infix,MAX_SIZE,stdin);
    infix_to_rpn(infix, rpn);
    printf("rpn: %s", rpn);
    //plot_function(rpn);
    
    return 0;
}