#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "pqueue.h"

struct s_pqueue {
    struct s_node *first;
    unsigned int size;
};

struct s_node {
    pqueue_elem elem;
    unsigned int prio;
    struct s_node *next;
};

static struct s_node * create_node(pqueue_elem e, unsigned int priority) {
    struct s_node *new_node = NULL;
    new_node = malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->prio = priority;
    new_node->next = NULL;
    assert(new_node->elem==e && new_node->prio == priority);
    return new_node;
}

static struct s_node * destroy_node(struct s_node *node) {
    assert(node != NULL);
    free(node);
    node = NULL;
    assert(node == NULL);
    return node;
}


static bool invrep(pqueue q) {
    assert(q != NULL);
    bool b = true;
    unsigned int real_size = 0;
    struct s_node *p;
    if(q->first != NULL){
        p = q->first;
        real_size++;
        while(p->next != NULL && b){
            b = p->prio <= p->next->prio;
            p = p->next;
            real_size++;
        }
    }
    b = real_size == q->size && b; 
    return b;
}

pqueue pqueue_empty(void) {
    pqueue q=NULL;
    q = malloc(sizeof(struct s_pqueue));
    q->first = NULL;
    q->size = 0;
    assert(invrep(q) && pqueue_is_empty(q));
    return q;
}

pqueue pqueue_enqueue(pqueue q, pqueue_elem e, unsigned int priority) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e, priority);
    struct s_node *p; 
    struct s_node *p_before;
    if (q->first == NULL){
        q->first = new_node;
        q->size++;
    } else {
        p = q->first;
        p_before = p;
        bool isnt_enqueue = true;
        while(isnt_enqueue){
            if(new_node->prio < p->prio){
                if (p == q->first){
                    q->first = new_node;
                    new_node->next = p;
                } else {
                    p_before->next = new_node;
                    new_node->next = p;
                }
                q->size++;
                isnt_enqueue = false;
            } else if (new_node->prio == p->prio){
                if (p->next != NULL){
                    if (p->next->prio != p->prio){
                    new_node->next = p->next;
                    p->next = new_node;
                    q->size++;
                    isnt_enqueue = false;
                    } else {
                        p_before = p;
                        p = p->next;
                    }
                } else {
                    new_node->next = p->next;
                    p->next = new_node;
                    q->size++;
                    isnt_enqueue = false;
                }
            } else if (p->next == NULL) {
                p->next = new_node;
                q->size++;
                isnt_enqueue = false;
            } else {
                p_before = p;
                p = p->next;
            }
        }
    }
    assert(invrep(q) && !pqueue_is_empty(q)); 
    return q;
}

bool pqueue_is_empty(pqueue q) {
    bool is_empty = q->first == NULL;
    return is_empty;
}

pqueue_elem pqueue_peek(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    pqueue_elem e;
    struct s_node *p = q->first;
    unsigned int max_prio = p->prio;
    e = p->elem;
    while(p->next != NULL){
        p = p->next;
        if (p->prio < max_prio){
            max_prio = p->prio;
            e = p->elem;
        }
    }
    assert(invrep(q));
    return e;
}

unsigned int pqueue_peek_priority(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node *p = q->first;
    unsigned int max_prio = p->prio;
    while(p->next != NULL){
        p = p->next;
        if (p->prio < max_prio){
            max_prio = p->prio;
        }
    }
    assert(invrep(q));
    return max_prio;
}

unsigned int pqueue_size(pqueue q) {
    assert(invrep(q));
    unsigned int size = q->size;
    return size;
}

pqueue pqueue_dequeue(pqueue q) {
    assert(invrep(q) && !pqueue_is_empty(q));
    struct s_node * killme = q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;
}

pqueue pqueue_destroy(pqueue q) {
    assert(invrep(q));
    struct s_node *node = q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}
