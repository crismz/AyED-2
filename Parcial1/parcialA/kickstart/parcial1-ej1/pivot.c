#include <stdbool.h>
#include <stdio.h>
#include "pivot.h"

bool is_pivot(int array[], unsigned int length, unsigned int piv) {
    unsigned int i,j;
    i = 0;
    j = length-1;
    while (i < piv)
    {
        if (array[i] <= array[piv]) {
            i++;
        }  else {
            return false;
        }
    }

    while (j > piv) {
        if (array[j] > array[piv]) {
            j--;
        } else {
            return false;
        }
    }
    
    return true;
}

int main () {
    bool res;
    unsigned int length,piv,i;
    printf("De el tamaño del arreglo\n");
    scanf("%u",&length);
    int array[length];
    for (i = 0; i < length; i++) {
        printf("De el elemento %u\n",i);
        scanf("%d",&array[i]);
    } 
    printf("Eliga el valor del pivote\n");
    scanf("%u",&piv);
    res = is_pivot(array,length,piv);
    printf("%d\n",res);
    return 0;
}
