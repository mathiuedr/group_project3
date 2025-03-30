#include <stdio.h>
#include "parser.h"
#include "graph.h"
#include "rpn.h"

#define MAX_SIZE 100
#define MAX_RPN_SIZE (MAX_SIZE * 2)

int main() {
    char infix[MAX_SIZE];
    char rpn[MAX_RPN_SIZE];
    fgets(infix,MAX_SIZE,stdin);
    
    infix_to_rpn(infix, rpn);
    if(check_rpn(rpn)){
        plot_function(rpn);
    }else{
        printf("n/a");
    }
    
    
    
    return 0;
}