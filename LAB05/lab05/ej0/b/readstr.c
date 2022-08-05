#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 20

int main(void) {
    char user_input[MAX_LENGTH];

    printf("Ingrese su nombre y apellido: ");
    fgets(user_input,MAX_LENGTH, stdin);
    
    /*
    unsigned int i = 0;                     // En vez de usar strrchr podemos usar un while hasta encontrar el elemento \n
    while (user_input[i] != '\n') {         // y luego reemplazarlo con '\0'
        i += 1;                             
    }
    user_input[i] = '\0';                                         
    */                                   

    char * r = strrchr(user_input,'\n');
    *r = '\0';

    printf("Te damos la bienvenida %s a este maravilloso programa!\n", user_input);

    return EXIT_SUCCESS;
}

