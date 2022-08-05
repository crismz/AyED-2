#include "array_helpers.h"
#include <stdio.h>


unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    FILE * fp;
    unsigned int result;
    unsigned int i = 0;
    fp = fopen(filepath,"r");
    fscanf(fp,"%u",&result);
    if (result > max_size) {
        printf("Arreglo demasiado grande");
    } else {
        for (i = 0; i < result; i++) {
            fscanf(fp,"%d",&array[i]);
        }
    }   
    fclose(fp);
    return result;
    
    
}

void array_dump(int a[], unsigned int length) {
    unsigned int i = 0;
    if (length == 0 && length <= 100000) {
        printf("[]");
    } if(length != 0 && length <= 100000) {
        printf("[");
        for (i = 0; i < length; i++) {
            if (i != length-1) {
              printf("%d, ",a[i]);
            } else {
              printf("%d]",a[i]);
            }
    }
    }
}
