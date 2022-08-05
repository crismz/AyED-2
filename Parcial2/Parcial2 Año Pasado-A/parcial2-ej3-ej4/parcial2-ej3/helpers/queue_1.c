#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue_1.h"

struct _s_queue {
    queue_elem elem;
    struct _s_queue *next;
};

queue queue_empty(void) {
    return NULL;
}

queue queue_enqueue(queue q, queue_elem e) {
    queue new_node = calloc(1, sizeof(struct _s_queue));
    new_node->elem= e;
    new_node->next = q;
    q = new_node;
    return q;
}

bool queue_is_empty(queue q) {
    return q == NULL;
}

queue_elem queue_first(queue q) {
    queue_elem elem;
    queue aux;
    if (q != NULL){
        aux = q;
        while (aux->next != NULL){
            aux = aux->next;
        }
        elem = aux->elem;
    }
    aux = NULL;

    return elem;
}
unsigned int queue_size(queue q) {
    unsigned int size=0;
    while (q != NULL) {
        size++;
        q = q->next;
    }
    return size;
}

queue queue_dequeue(queue q) {
    queue aux;
    if (q != NULL){
        if (q->next == NULL){
            free(q);
            q = NULL;
        } else {
            aux = q;
            while (aux->next->next != NULL){
                aux = aux->next;
            }
             free(aux->next);
             aux->next = NULL;
        }
        
    }
    return q;
}

queue queue_destroy(queue q) {
    queue aux=NULL;
    while (q != NULL) {
        aux=q;
        q = q->next;
        free(aux);
    }
    return q;
}

