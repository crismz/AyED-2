#include <assert.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <stdio.h>


#include "cost.h"
#include "graph.h"
#include "mini_set.h"

vertex_t min_elem(set vertexs,cost_t * d,vertex_t vert_actual,unsigned int cardinal){
    int min = INT_MAX;                      // +Inf
    vertex_t c = vert_actual;
    for (unsigned int i = 0; i < cardinal; i++){
        if (set_member(i,vertexs) && i != vert_actual && d[i] < min ){
            min = d[i];
            c = i;
        }
    }
    return c;
}


cost_t min(cost_t a ,cost_t b){
    cost_t min;
    if (a <= b){
        min = a;
    } else {
        min = b;
    }
    return min;
}

cost_t *dijkstra(graph_t graph, vertex_t init) {
    vertex_t c;
    vertex_t vert_actual = init;
    bool no_conexo = true;
    set vertexs = set_empty();
    cost_t * res = calloc(graph_max_vertexs(graph),sizeof(cost_t));
    for (unsigned int i = 0; i < graph_max_vertexs(graph); ++i){
        vertexs = set_add(vertexs,i);
    }
    unsigned int elems_vertexs = set_cardinal(vertexs);
    vertexs = set_elim(vertexs,init);
    for (vertex_t i = 0; i < graph_max_vertexs(graph); ++i){
        res[i] = graph_get_cost(graph,init,i);
    }
    while (!set_is_empty(vertexs) && no_conexo){
        c = min_elem(vertexs,res,vert_actual,elems_vertexs);
        no_conexo = c != vert_actual;
        vert_actual = c;
        vertexs = set_elim(vertexs,c);
        for (unsigned int i = 0; i < elems_vertexs; ++i){
            if (set_member(i,vertexs)){
                if (graph_get_cost(graph,c,i) == INT_MAX) {
                    res[i] = res[i];
                } else {
                    res[i] = min(res[i], res[c] + graph_get_cost(graph,c,i));
                }
                
            }
        }
        
    }
    set_destroy(vertexs);
    return res;
}
