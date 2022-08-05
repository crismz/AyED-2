#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

int main(){
    stack s = stack_empty();

    for(int i = 0; i < 10; i++){
        s = stack_push(s,i);
    }
    printf("%u\n",stack_size(s));
    stack_elem e = stack_top(s);
    printf("el elem top es %d\n",e);
 
    s = stack_pop(s);
    s = stack_pop(s);
    printf("%u\n",stack_size(s));
    e = stack_top(s);
    printf("el elem top es %d\n",e);

    stack_elem *array = stack_to_array(s);
    printf("%d\n",array[2]);
    
    stack p = stack_empty();
    p = stack_push(p,5);
    p = stack_pop(p);

    p = stack_push(p,10);

    stack_destroy(p);
    stack_destroy(s);

    return 0; 
}