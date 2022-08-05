#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pstack.h"

struct s_pstack {
    struct s_node * * nodes_prio;
    unsigned int size;
    priority_t max_prio;
};

struct s_node {
    pstack_elem elem;
    struct s_node * next;
    priority_t prio;                // Se agrega para chequear que cumpla la invariante
};

static struct s_node * create_node(pstack_elem e) {
    struct s_node *new_node = NULL;
    assert(new_node==NULL);
    new_node = malloc(sizeof(struct s_node));
    new_node->elem = e;
    new_node->prio = 0;
    new_node->next = NULL;
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    free(node);
    node = NULL;
    return node;
}


static bool invrep(pstack s) {
    priority_t i = 0;
    unsigned int real_size = 0;
    struct s_node * p;
    bool prio_good = true;
    while(i <= s->max_prio && prio_good){
        p = s->nodes_prio[i];
        while(p != NULL && prio_good){
            prio_good = i == p->prio;
            real_size++;
            p = p->next;
        }
        i++;
    }
    bool inv_good = prio_good && real_size == s->size;
    return inv_good;
}

pstack pstack_empty(priority_t max_priority) {
    pstack s=NULL;
    s = malloc(sizeof(struct s_pstack));
    s->nodes_prio = calloc(max_priority + 1,sizeof(struct s_node *));
    for (unsigned int i=0;i <= max_priority; i++){
        s->nodes_prio[i] = NULL;
    }
    s->size = 0;
    s->max_prio = max_priority;
    assert(invrep(s) && pstack_is_empty(s));
    return s;
}

pstack pstack_push(pstack s, pstack_elem e, priority_t priority) {
    assert(invrep(s) && priority <= s->max_prio);
    struct s_node * new_node = create_node(e);
    new_node->prio = priority;                  // Para hacer invariante
    if(s->nodes_prio[priority] == NULL){
        s->nodes_prio[priority] = new_node;
    } else {
        new_node->next = s->nodes_prio[priority];
        s->nodes_prio[priority] = new_node;
    }
    s->size++;
    assert(invrep(s) && !pstack_is_empty(s));
    return s;
}

bool pstack_is_empty(pstack s) {
    assert(invrep(s));
    unsigned int i = 0;
    bool is_empty = true;
    while(i <= s->max_prio && is_empty){
        is_empty = s->nodes_prio[i] == NULL;
        i++;
    }
    return is_empty;
}

pstack_elem pstack_top(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t i = s->max_prio;
    pstack_elem e;
    while(s->nodes_prio[i] == NULL){
        i--;
    }
    e = s->nodes_prio[i]->elem;
    assert(invrep(s));
    return e;
}

priority_t pstack_top_priority(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    priority_t prio = s->max_prio;
    while(s->nodes_prio[prio] == NULL){
        prio--;
    }
    assert(invrep(s));
    return prio;
}

size_t pstack_size(pstack s) {
    assert(invrep(s));
    unsigned int size = s->size;
    return size;
}

pstack pstack_pop(pstack s) {
    assert(invrep(s) && !pstack_is_empty(s));
    struct s_node * killme;
    priority_t prio = s->max_prio;
    while(s->nodes_prio[prio] == NULL){
        prio--;
    }
    killme = s->nodes_prio[prio];
    s->nodes_prio[prio] = killme->next;
    killme = destroy_node(killme);
    s->size--;
    assert(invrep(s));
    return s;
}

pstack pstack_destroy(pstack s) {
    assert(invrep(s));
    struct s_node * killme;
    priority_t i = 0;
    while(i <= s->max_prio){
        while(s->nodes_prio[i] != NULL){
            killme = s->nodes_prio[i];
            if (killme != NULL){
                s->nodes_prio[i] = killme->next;
                killme = destroy_node(killme);
            }
        }
        i++;
    }
    free(s->nodes_prio);
    free(s);
    s = NULL;
    assert(s == NULL);
    return s;
}
