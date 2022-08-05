#include "sorted.h"
#include <stdbool.h>
#include <stdio.h>

unsigned int sorted_until(int array[], unsigned int size) {
    unsigned int i = 0;
    bool sorted = true;
    if (size == 0) {
        return 0;
    } 
    while (sorted && i < size-1) {
        if (array[i] <= array[i+1]) {
            i++;
        } else {
            sorted = false;
        }
    }
    
    return i;
}

int main () {
    unsigned int length,i,res;
    printf("De el tamaño del arreglo\n");
    scanf("%u",&length);
    int array[length];
    for (i = 0; i < length; i++) {
        printf("De el elemento %u\n",i);
        scanf("%d",&array[i]);
    } 
    res = sorted_until(array,length);
    printf("%u\n",res);
    return 0;
}