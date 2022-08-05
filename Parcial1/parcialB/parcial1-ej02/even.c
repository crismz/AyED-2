#include <stdbool.h>
#include <stdio.h>
#include "even.h"

bool is_even_sorted(int array[], unsigned int length) {
    unsigned int i = 0;
    bool sorted = true;
    while (i < length-2 && sorted) {
        if (array[i] <= array[i+2]){ 
            i=i+2;
        } else {
            sorted = false;
        }
    }
    return sorted;
}

int main () {
    bool res;
    unsigned int length,i;
    printf("De el tamaño del arreglo\n");
    scanf("%u",&length);
    int array[length];
    for (i = 0; i < length; i++) {
        printf("De el elemento %u\n",i);
        scanf("%d",&array[i]);
    } 
    res = is_even_sorted(array,length);
    printf("%u\n",res);
    return 0;
}