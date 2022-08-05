#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <assert.h>

#include "truco.h"

int main(){
    char palo;
    int num;
    
    printf("Indica el palo de la carta con su inicial\n");
    scanf("%c",&palo);
    printf("Indica el número de la  misma carta\n");
    scanf("%d",&num);
    truco_card card_1 = truco_card_new(num,palo);
    
    palo = '\0';
    num = 0;
    printf("Indica el palo de la carta con su inicial\n");
    scanf("\n%c",&palo);
    printf("Indica el número de la  misma carta\n");
    scanf("%d",&num);  
    truco_card card_2 = truco_card_new(num,palo);

    if(truco_card_win(card_1,card_2)){
        truco_card_dump(card_1);
        truco_card_dump(card_2);
    } else if(truco_card_win(card_2,card_1)){
        truco_card_dump(card_2);
        truco_card_dump(card_1);
    } else if(truco_card_tie(card_2,card_1)){
        printf("¡La mano está parda!\n");
        truco_card_dump(card_1);
        truco_card_dump(card_2);
    }
    truco_card_destroy(card_1);
    truco_card_destroy(card_2);
    return 0;
}
