#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node *first;
    unsigned int size;
};

struct s_node {
    pstack_elem elem;
    priority_t prio;
    struct s_node *next;
};

static struct s_node * create_node(pstack_elem e, priority_t priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->prio = priority;
    new_node->next = NULL;
    assert(new_node->elem == e && new_node->prio == priority);
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pstack s) {
    assert(s != NULL);
    bool b = true;
    unsigned int real_size = 0;
    struct s_node *p;
    if (s->first != NULL){
        p = s->first;
        real_size++;
        while(p->next != NULL && b){
            b = (p->prio >= p->next->prio); 
            p = p->next;
            real_size++;
        }
    }
    b = b && real_size == s->size;
    return b;
}

pstack pstack_empty(void) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->first = NULL;
    s->size = 0;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *p = NULL;
    struct s_node *p_before = NULL;
    if (s->first == NULL){
        s->first = new_node;
        s->size++;
    } else {
        p = s->first;
        while(p->next != NULL && new_node->prio < p->prio){
            p_before = p;
            p = p->next;
        }
        if (s->first == p){
            s->first = new_node;
            new_node->next = p;
            s->size++;
        } else if (p->next == NULL) {
            p->next = new_node;
            s->size++;
        } else {
            p_before->next = new_node;
            new_node->next = p;
            s->size++;
        }
    }
    assert(invrep(s) && !pstack_is_empty(s)); 
    return s;
}

bool pstack_is_empty(pstack s) {
    bool is_empty = s->first == NULL;
    assert(invrep(s));
    return is_empty;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s)); 
    pstack_elem e = s->first->elem;
    assert(invrep(s)); 
    return e;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s)); 
    priority_t prio = s->first->prio;
    assert(invrep(s));
    return prio;
}

unsigned int pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size=0;
    size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s)); 
    struct s_node *killme = s->first;
    s->first = s->first->next;
    killme = destroy_node(killme);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node *node=s->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}

