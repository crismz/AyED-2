#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "truco.h"

struct _s_truco_card {
    int num;
    char p;
};

#define ESPADA "ESPADA"
#define BASTO  "BASTO"
#define ORO    "ORO"
#define COPA   "COPA"

static const char *suit_str(char p) {
    const char *str;
    if (p == 'e') {
        str = ESPADA;
    } else if (p=='b') {
        str = BASTO;
    } else if (p=='o') {
        str = ORO;
    } else if (p=='c') {
        str = COPA;
    }
    return str;
}

static void dump(int num, char suit) {
    printf(" ----------------\n"
           " : %2d           :\n"
           " :              :\n"
           " :              :\n"
           " :    ""%-7s""   :\n"
           " :              :\n"
           " :              :\n"
           " :              :\n"
           " :           %2d :\n"
           " ----------------\n",
           num, suit_str(suit), num);
}

static int card_rank(int num, char suit) {
    int rank=0;

    if (4 <= num && num <= 12) { // 4 ~ 12
    
        if (num == 4) {
            rank = 0;
        } else if (num == 5) {
            rank = 1;
        } else if (num == 6) {
            rank = 2;
        } else if (num == 7 && (suit == 'c' || suit == 'b')) {
            rank = 3;
        } else if (num == 10) {
            rank = 6;
        } else if (num == 11) {
            rank = 7;
        } else if (num == 12) {
            rank = 8;
        }
    } else { // 1 ~ 3
        if (num == 1 && (suit == 'c' || suit == 'o')) {
            rank = 9;
        } else if (num == 2) {
            rank = 10;
        } else if (num == 3) {
            rank = 11;
        } else if (num == 7 && suit == 'o') {
            rank = 12;
        } else if (num == 7 && suit == 'e') {
            rank = 13;
        } else if (num == 1 && suit == 'b') {
            rank = 14;
        } else if (num == 1 && suit == 'e') {
            rank = 15;
        }
    }
    return rank;
}

static bool invrep(truco_card c) {
    bool valid_card=false;
    if (c->num >= 1 && c->num <= 12 && c->num != 8 && c->num != 9){
        if (c->p == 'e' || c->p == 'o' || c->p == 'c' || c->p == 'b'){
            valid_card = true;
        }
    }
    return valid_card;
}

truco_card truco_card_new(int num, char p) {
    truco_card card;
    card = malloc(sizeof(struct _s_truco_card));
    card->num = num;
    card->p = p;
    invrep(card);
    return card;
}

bool truco_card_win(truco_card a, truco_card b) {
    invrep(a);
    invrep(b);
    bool card_a_win=false;
    int rank_a = card_rank(a->num,a->p);
    int rank_b = card_rank(b->num,b->p);
    if(rank_a > rank_b){
        card_a_win = true;
    }
    return card_a_win;
}

bool truco_card_tie(truco_card a, truco_card b) {
    invrep(a);
    invrep(b);
    bool is_a_tie=false;
    int rank_a = card_rank(a->num,a->p);
    int rank_b = card_rank(b->num,b->p);
    if(rank_a == rank_b){
        is_a_tie = true;
    }
    return is_a_tie;
}

void truco_card_dump(truco_card c) {
    invrep(c);
    dump(c->num,c->p);
}

truco_card truco_card_destroy(truco_card c) {
    invrep(c);
    free(c);
    c = NULL;
    return c;
}
