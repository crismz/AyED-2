#include <stdio.h>    /* printf(), scanf() */
#include <stdbool.h>  /* tipo bool         */

#include <assert.h>   /* assert() */

#define ARRAY_SIZE 10

struct max_min_result {
    int max_value;
    int min_value;
    unsigned int max_position;
    unsigned int min_position;
};

struct max_min_result compute_max_min(int array[],  int length)
{
    assert(length > 0);
     
    int max_actual = array[0];
    int min_actual = array[0];
    int max_position = 0;
    int min_position = 0;
    int i = 1;
    while (i < length) {
        if (array[i] >= max_actual) {
            max_actual = array[i];
            max_position = i; 
        } if (array[i] <= min_actual) {
            min_actual = array[i];
            min_position = i;
        }
        i++;
    }
    
    struct max_min_result result;
    result.max_value = max_actual;
    result.min_value = min_actual;
    result.max_position = max_position;
    result.min_position = min_position;

    // IMPLEMENTAR

    return result;
}

int main(void)
{
    int array[ARRAY_SIZE] = { 4, -1, 5, 8, 9, 0, 3, 6, 0, 0 };

    for (int i = 0; i < 10; i++) {
        printf("Ingrese el valor de la posicion %d del array \n", i);
        scanf("%d",&array[i]);
    };
    
    struct max_min_result result = compute_max_min(array, ARRAY_SIZE);
    printf("Máximo: %d\n", result.max_value);
    printf("Posición del máximo: %u\n", result.max_position);
    printf("Mínimo: %d\n", result.min_value);
    printf("Posición del mínimo: %u\n", result.min_position);
    return 0;
}

