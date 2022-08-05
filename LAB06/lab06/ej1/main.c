/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "abb.h" /* TAD abb */


void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;

    if (argc < 2) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return (result);
}

abb abb_from_file(const char *filepath) {
    FILE *file = NULL;
    abb read_tree;

    read_tree = abb_empty();
    file = fopen(filepath, "r");
    if (file == NULL) {
        fprintf(stderr, "File does not exist.\n");
        exit(EXIT_FAILURE);
    }
    unsigned int i = 0u;
    unsigned int size = 0u;
    int res = 0;
    res = fscanf(file, " %u ", &size);
    if (res != 1) {
        fprintf(stderr, "Invalid format.\n");
        exit(EXIT_FAILURE);
    }
    while (i < size) {
        abb_elem elem;
        res = fscanf(file," %d ", &(elem));
        if (res != 1) {
            fprintf(stderr, "Invalid array.\n");
            exit(EXIT_FAILURE);
        }
        read_tree = abb_add(read_tree, elem);

       ++i;
    }
    fclose(file);
    return read_tree;
}

int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);

    /* parse the file to obtain an abb with the elements */
    abb tree = abb_from_file(filepath);

    /*dumping the tree*/
    abb_dump(tree);
    if (!abb_is_empty(tree)) {
        printf("\n");
        printf("raiz: %d\n minimo: %d\n maximo: %d\n", abb_root(tree),
                                                       abb_min(tree),
                                                       abb_max(tree));
    } else {
        printf("\nÁrbol vacío\n");
    }


    bool exit_program = false;
    while(!exit_program){
        unsigned int opcion;
        printf("\n\nSeleccione una de las siguiente opciones \n1 ........ Mostrar árbol por pantalla \n2 ........ Agregar un elemento \n3 ........ Eliminar un elemento \n4 ........ Chequear existencia de elemento \n5 ........ Mostrar longitud del árbol \n6 ........ Mostrar raiz, máximo y mínimo del árbol \n7 ........ Salir \n\n\n");
        scanf("%u",&opcion);

        if (opcion == 1){
            abb_dump(tree);
            printf("\n");
        } else if (opcion == 2){
            abb_elem e;
            printf("De el elemento que quiere agregar\n");
            scanf("%d",&e);
            abb_add(tree,e);
        } else if (opcion == 3){   //Ver error, me da cuando intento eliminar una hoja
            abb_elem e;
            printf("De el elemento que quiere eliminar\n");
            scanf("%d",&e);
            abb_remove(tree,e);
        } else if (opcion == 4){
            abb_elem e;
            printf("De el elemento que quiere chequear existencia\n");
            scanf("%d",&e);
            if(abb_exists(tree,e)){
                printf("El elemento %d existe en el árbol\n",e);
            } else {
                printf("El elemento %d NO existe en el árbol\n",e);
            }
        } else if (opcion == 5){
            printf("La longitud del árbol es %u\n",abb_length(tree));
        } else if (opcion == 6){
            printf("El máx es %d\n",abb_max(tree));
            printf("El min es %d\n",abb_min(tree));
            printf("La raíz es %d\n",abb_root(tree));
        } else if (opcion == 7){
            exit_program = true;
            tree = abb_destroy(tree);
        }
    }
    
    return (EXIT_SUCCESS);
}
