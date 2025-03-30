#include "utils.h"

int is_space(int c){
    return (c == ' '  || 
            c == '\f' || 
            c == '\n' || 
            c == '\r' || 
            c == '\t' || 
            c == '\v');
}
int is_alpha(int c){
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'));
}
int is_digit(int c){
    return (c >= '0' && c <= '9');
}