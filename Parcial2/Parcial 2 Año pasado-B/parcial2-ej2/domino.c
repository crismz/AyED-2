#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "domino.h"

struct _s_domino {
    unsigned int top;
    unsigned int bottom;
};


/* auxiliary functions for dumping */

static char mark(bool b) {
    return b ? 'O' : ' ';
}

static void dump_num(int num) {
  printf("      | %c     %c |\n",
         mark(num > 1), mark(num > 3));
  printf("      | %c  %c  %c |\n",
         mark(num > 5), mark(num % 2 == 1), mark(num > 5));
  printf("      | %c     %c |\n",
         mark(num > 3), mark(num > 1));
}

static void dump_double_num(int num) {
  printf(" --------------------- \n");
  printf(" | %c  %c  %c ", mark(num > 3), mark(num > 5), mark(num > 1));
  printf( "| %c  %c  %c |\n", mark(num > 3), mark(num > 5), mark(num > 1));

  printf(" |    %c    ", mark(num % 2 == 1));
  printf( "|    %c    |\n", mark(num % 2 == 1));

  printf(" | %c  %c  %c ", mark(num > 1), mark(num > 5), mark(num > 3));
  printf( "| %c  %c  %c |\n", mark(num > 1), mark(num > 5), mark(num > 3));
  printf(" --------------------- \n");
}

void dump(int num_up, int num_down) {
    /* Pretty dump funcion for cool visualization :) */
    if (num_up != num_down)  {
        printf("      ----------- \n");
        dump_num(num_up);
        printf("      |---------| \n");
        dump_num(num_down);
        printf("      ----------- \n");
    } else {
        dump_double_num(num_up);
    }
}

/* Representation invariant */

static bool invrep(domino p) {
    bool valid_domino=false;
    if ((p->top == 0 || p->top == 1 || p->top == 2 || p->top == 3 
        || p->top == 4  || p->top == 5 || p->top == 6)    &&
        (p->bottom == 0 || p->bottom == 1 || p->bottom == 2 || p->bottom == 3 
        || p->bottom == 4  || p->bottom == 5 || p->bottom == 6)){
           valid_domino = true;
        }
    return valid_domino;
}

/* Public functions */

domino domino_new(int num_up, int num_down) {
    domino p;
    p = malloc(sizeof(struct _s_domino));
    p->top = num_up;
    p->bottom = num_down;
    assert(invrep(p));
    return p;
}

bool domino_is_double(domino p) {
    assert(invrep(p));
    bool is_double=false;
    if (p->top == p->bottom){
        is_double = true;
    }
    return is_double;
}

bool domino_eq(domino p1, domino p2) {
    assert(invrep(p1));
    assert(invrep(p2));
    bool equals=false;
    if ((p1->top == p2->top && p1->bottom == p2->bottom) || (p1->top == p2->bottom && p1->bottom == p2->top)){
        equals = true;
    }
    return equals;
}

bool domino_matches(domino p_top, domino p_bottom) {
    assert(invrep(p_top));
    assert(invrep(p_bottom));
    assert(!domino_eq(p_top,p_bottom));
    bool is_match=false;
    if (p_top->bottom == p_bottom->top){
        is_match = true;
    }
    return is_match;
}

domino domino_flip(domino p) {
    assert(invrep(p));
    unsigned int aux = p->top;
    p->top = p->bottom,
    p->bottom = aux;
    return p;
}

void domino_dump(domino p) {
    assert(invrep(p));
    dump(p->top,p->bottom);
}

domino domino_destroy(domino p) {
    assert(invrep(p));
    free(p);
    return p;
}

