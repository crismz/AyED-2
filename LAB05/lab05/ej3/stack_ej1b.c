#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct _s_stack {
    struct node * first;
    // index comienza en 0 con el ultimo elemento del stack
    unsigned int index;                                     
}_s_stack;                                              


typedef struct node {
    stack_elem elem;
    struct node * next;
} node;



stack stack_empty(){
    stack p;
    p = malloc(sizeof(_s_stack));
    p->index = 0;
    p->first = NULL; 
    return p;
}

stack stack_push(stack s, stack_elem e){
    if (s->first == NULL){
        s->first = malloc(sizeof(node));
        s->first->elem = e;
        s->first->next = NULL;
        s->index = 1;
    } else {
        node * p = s->first;
        s->first = NULL;
        s->first = malloc(sizeof(node));
        s->first->elem = e;
        s->first->next = p;
        s->index++;
    }
    return s;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    node * p;
    p = s->first;
    s->first = s->first->next;
    free(p);
    s->index--;
    return s;
}

unsigned int stack_size(stack s){
    unsigned int l;
    l = s->index;
    return l;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->first->elem;
}

stack stack_copy(stack s){
    assert(!stack_is_empty(s));
    stack q;
    node * p;
    q = malloc(sizeof(_s_stack));
    q->first = NULL;
    p = s->first;
    while (p != NULL){
        stack_push(q,p->elem);
        p = p->next;
    }
    p = NULL;
    q->index = s->index;
    return q;
}   


stack_elem *stack_to_array(stack s){
    stack_elem *array = NULL;
    if(s->first != NULL){
    stack p = stack_copy(s);
    unsigned int l = stack_size(p);

    if (l!=0) {
        array = calloc(l, sizeof(stack_elem));
        for (unsigned int i=0; i < l; i++){
            array[i] = stack_top(p);
            p = stack_pop(p);
        }
    }
    stack_destroy(p);
    }
    return array;
}

stack stack_destroy(stack s){
    node *p = s->first;
    node *q;
    while(p != NULL){
        q = p->next;
        free(p);
        p = q;
    }
    p = NULL;
    q = NULL;
    
    free(s);

    return s;
}

bool stack_is_empty(stack s){
    return s->first == NULL;
}