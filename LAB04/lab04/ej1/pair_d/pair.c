#include "pair.h"
#include <stdlib.h>

struct s_pair_t {
    elem fst;
    elem snd;
};

pair_t pair_new(int x, int y){
    pair_t pair = malloc(sizeof(pair_t));
    pair->fst = x;
    pair->snd = y;
    return pair;
}


int pair_first(pair_t p) {
 // PRE: {p --> (x, y)}
    return p->fst;
}

int pair_second(pair_t p) {
 // PRE: {p --> (x, y)}
    return p->snd;
}
pair_t pair_swapped(pair_t p) {
 //PRE: {p --> (x, y)}
    pair_t s = malloc(sizeof(pair_t));
    s->fst = p->snd;
    s->snd = p->fst;
    return s;
}

pair_t pair_destroy(pair_t p) {
    free(p);
    return p;
}