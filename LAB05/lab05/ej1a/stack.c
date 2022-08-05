#include <stdlib.h>
#include <assert.h>
#include "stack.h"

typedef struct _s_stack {
    struct s_node *first;
    unsigned int size;
}_s_stack;

struct s_node {
    stack_elem elem;
    struct s_node *next;
};

struct s_node* create_node(stack_elem e){
    struct s_node *new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

struct s_node* destroy_node(struct s_node *node){
    free(node);
    node = NULL;
    return node;
}



stack stack_empty(){
    stack s = malloc(sizeof(_s_stack));
    s->first = NULL;
    s->size = 0;
    return s;
}

stack stack_push(stack s, stack_elem e){
    struct s_node *new_node = create_node(e);
    new_node->next = s->first;
    s->first = new_node;
    s->size++;
    return s;
}

stack stack_pop(stack s){
    assert(!stack_is_empty(s));
    struct s_node *p;
    p = s->first;
    s->first = s->first->next;
    free(p);
    s->size--;
    return s;
}

unsigned int stack_size(stack s){
    return s->size;
}

stack_elem stack_top(stack s){
    assert(!stack_is_empty(s));
    return s->first->elem;
}

stack_elem *stack_to_array(stack s){
    stack_elem *array; 
    if (s->first != NULL) {
        array = calloc(s->size,sizeof(stack_elem));
        struct s_node *p = s->first;
        for (int i=s->size-1; 0 <= i; i--){
            array[i] = p->elem;
            p = p->next;
        }
    } else {
        array = NULL;
    }
    return array;
}

stack stack_destroy(stack s){
    struct s_node *p = s->first;
    struct s_node *killme;
    while(p != NULL){
        killme = p;
        p = p->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    return s;
}

bool stack_is_empty(stack s){
    return s == NULL;
}