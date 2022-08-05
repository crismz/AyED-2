#ifndef _LIST_H
#define _LIST_H

#include <stdbool.h>

/* list as a pointer to struct to guarantee encapsulation */
typedef struct node_t * list;
typedef int elem_list;

/* Constructors */
list list_empty(void);
/*
    Create a new list empty. Allocates new memory.
*/

list list_addl(list l, elem_list e);
/* 
    Add the elem e at the start of the list 
*/


/* Operations */
bool list_is_empty(list l);
/*
    Return True if l is empty
*/

elem_list list_head (list l);
/*
    PRE: not list_is_empty(l)
    Return the firts element of the list l
*/

list list_tail(list l);
/*
    PRE: not list_is_empty(l)
    Delete the first element of the list l
*/

list list_addr(list l, elem_list e);
/*
    Add element e at the end of l
*/

unsigned int list_length(list l);
/*
    Return how many elements have l
*/

list list_concat(list l1, list l2);
/*
    Add at the end of l1 all elements of l2
*/

elem_list list_index(list l, unsigned int n);
/*
    PRE: length(l) > n
    Return the element in the position n of the list l
*/

list list_take(list l, unsigned int n);
/*
    Keep in l first n elements and delete the rest
*/

list list_drop(list l, unsigned int n);
/*
    Delete the first n elements of l
*/

list list_copy(list l);
/*
    Create a list and copy l
*/

list list_destroy(list l);
/*
    Frees memory for l
*/

#endif
