#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 1000

static void dump(char a[], unsigned int length) {
    printf("\"");
    for (unsigned int j=0u; j < length; j++) {
        printf("%c", a[j]);
    }
    printf("\"");
    printf("\n\n");
}

unsigned int data_from_file(const char *path, unsigned int indexes[], char letters[], unsigned int max_size) {
    FILE *fp;
    unsigned int contador;
    contador = 0;
    fp = fopen(path,"r");
    while(!feof(fp)) {
        fscanf(fp,"%u '%c' \n",&indexes[contador],&letters[contador]);     //Se el \n para que pase a la siguiente linea sino no lo hace
        contador = contador + 1;
        if (contador > max_size) {
            printf("Los elementos superan el max_size\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(fp);
    return contador;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;
    if(argc != 2) {
        exit(EXIT_FAILURE);
    }
    filepath = argv[1];
    unsigned int indexes[MAX_SIZE];
    char letters[MAX_SIZE];
    char sorted[MAX_SIZE];
    unsigned int length=0; 
    //  .----------^
    //  :
    // Debe guardarse aqui la cantidad de elementos leidos del archivo
    
    length = data_from_file(filepath,indexes,letters, MAX_SIZE);
    printf("%u",length);
    for (unsigned int i=0u; i < length; i++) {
        for (unsigned int j=0u; j < length; j++) {
            if (indexes[j] == i) {
                sorted[i] = letters[j];
            }
        }
    }

    dump(sorted, length);

    return EXIT_SUCCESS;
}

