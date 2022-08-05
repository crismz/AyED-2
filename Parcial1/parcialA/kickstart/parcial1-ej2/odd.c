#include <stdbool.h>
#include <stdio.h>
#include "odd.h"

bool is_odd_sorted(int array[], unsigned int length) {
    int x = array[1];
    for (unsigned int  i = 1; i < length; i=i+2)
    {   
        if (x > array[i]) {
            return false;
        }
        x = array[i];
    }
    
    return true;
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
    res = is_odd_sorted(array,length);
    printf("%d\n",res);
    return 0;
}