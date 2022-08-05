#include "list.h"
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>

typedef struct node_t {
    int elem;
    struct node_t * next;
} node;

list list_empty(void) {
    return NULL;
}

list list_addl (list l, elem_list e) {
    node * p;
    p = malloc(sizeof(node));
    p->elem = e;
    p->next = l;
    l = p;
    return l;
}

bool list_is_empty(list l) {
    bool b = l == NULL;
    return b;
}

elem_list list_head (list l) {
    assert(!list_is_empty(l));
    elem_list e = l->elem;
    return e;
}

list list_tail (list l) {
    assert(!list_is_empty(l));
    l = l->next;
    return l;
}

list list_addr (list l, elem_list e) {
    node * p;
    node * q;
    q = malloc(sizeof(node));
    q->elem = e;
    q->next = NULL;
    if (!list_is_empty(l)) {
        p = l;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = q;
    }
    else {
        l = q;
    }
    return l;
}   

unsigned int list_length (list l) {
    node * p = l;
    unsigned int n = 0;
    while (p != NULL) {
        n++;
        p = p->next;       
    }
    return n;
}

list list_concat (list l1, list l2) {
    node * p;
    list copy;
    copy = list_copy(l2);
    if (l1 == NULL) {
        l1 = copy;
    }
    else {
        p = l1;
        while (p->next != NULL) {
            p = p->next;
        } 
        p->next = copy;
    }
    return l1;
}

elem_list list_index (list l,unsigned int n) {
    assert(list_length(l) >= n);
    node * p = l;
    for (unsigned int i = 1u; i < n; i++) {
        p = p->next;
    }
    elem_list e = p->elem;
    return e;
}

list list_take (list l, unsigned int n) {
    node * p;
    node * q;
    p = l;
    for (unsigned int i = 1; i < n; i++) {
        if (p != NULL) {
            p = p->next;
        }
    }
    if (p != NULL) {
        q = p;
        p = p->next;
        q->next = NULL;
    }
    while (p != NULL) {
        q = p;
        p = p->next;
        free(q);
    }
    return l;
}

list list_drop (list l, unsigned int n) {
    node * p;
    for (unsigned int i = 1; i <= n; i++) {
        if (p != NULL) {
            p = l;
            l = p->next,
            free(p);
        }
    }
    return l;
}

list list_copy (list l) {
    list copy = list_empty();
    node * p;
    p = l;
    while(p != NULL) {
        copy = list_addr(copy,p->elem);
        p = p->next;
    }
    return copy;
}

list list_destroy (list l) {
    node * q = l;
    while (l != NULL) {
        l = l->next;
        free(q);
        q = l;
    }
    return l;
}