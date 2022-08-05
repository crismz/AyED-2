#include <stdlib.h>
#include <assert.h>
#include "stack.h"

//Invariante para todas las funciones: que s->size <= s->capacity
struct _s_stack {
    stack_elem *elems;      // Arreglo de elementos
    unsigned int size;      // Cantidad de elementos en la pila
    unsigned int capacity;  // Capacidad actual del arreglo elems
}_s_stack;

stack stack_empty(){
    stack s = malloc(sizeof(_s_stack));
    s->size = 0;
    s->capacity = 0;
    s->elems = NULL;
    return s;
}

stack stack_push(stack s, stack_elem e){
    assert(s->size <= s->capacity);
    // Reservar memoria si hace falta
    if(s->size == s->capacity){
        size_t cap_aux = s->size == 0 ? 1 * sizeof(stack_elem) : 2 * s->capacity;
        s->capacity = cap_aux;
        s->elems = realloc(s->elems,cap_aux * sizeof(stack_elem));
    }
    
    s->elems[s->size] = e;
    s->size += 1;
    
    return s;
}

stack stack_pop(stack s){
    assert(s->size <= s->capacity);
    assert(!stack_is_empty(s));
    s->size -= 1;
    return s;
}

unsigned int stack_size(stack s){
     assert(s != NULL);
    assert(s->size <= s->capacity);
    return s->size;
}

stack_elem stack_top(stack s){
    assert(s->size <= s->capacity);
    assert(!stack_is_empty(s));
    return s->elems[(s->size)-1];
}

bool stack_is_empty(stack s){
    assert(s != NULL);
    assert(s->size <= s->capacity);
    return s->size == 0;
}

stack_elem *stack_to_array(stack s){
    assert(s != NULL);
    assert(s->size <= s->capacity);
    unsigned int l = stack_size(s);
    stack_elem* array = malloc(l * sizeof(stack_elem));
    for (int i=l-1; i >= 0; i--){
        array[i] = s->elems[i];  
    }
    return array;
}

stack stack_destroy(stack s){
    assert(s != NULL);
    assert(s->size <= s->capacity);
    free(s->elems);
    free(s);
    return NULL;
}