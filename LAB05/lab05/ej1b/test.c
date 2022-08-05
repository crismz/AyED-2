#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main (){
    stack s = stack_empty();
    for (int i=5; i >= 0; i--){
        s = stack_push(s,i);
    }
    stack_destroy(s);
    return 0;
}