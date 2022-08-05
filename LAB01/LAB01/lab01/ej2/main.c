/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

unsigned int array_from_file(int array[],
           unsigned int max_size,
           const char *filepath) {
    FILE * fp;
    unsigned int result;
    unsigned int i = 0;

    char arr[MAX_SIZE];

    printf("De el tamano y los elementos del array\n");
    fgets(arr,MAX_SIZE,stdin);

    fp = fopen(filepath,"r+");
    fprintf(fp,arr);
    rewind(fp);
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


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
