/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include "mybool.h"
#include <stdio.h>
#include <stdlib.h>
#include "array_helpers.h"


/* Maximum allowed length of the array */
#define MAX_SIZE 100000


char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    mybool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}


int main(int argc, char *argv[]) {
    char *filepath = NULL;
    unsigned int halfOfArray;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);

    /* invertir el array*/
    halfOfArray = length/2;
    
    for (unsigned int i = 0; i < halfOfArray; i++) {
        int endArray = length-1-i;
        array_swap(array,i,endArray);
   }
    

    /*dumping the array*/
    array_dump(array, length);
    if(array_is_sorted(array,length)) {
        printf("El arreglo esta ordenado");
    } else {
        printf("El arreglo no esta ordenado");
    }
    
    return EXIT_SUCCESS;
}
