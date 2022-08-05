#include <stdlib.h>
#include <stdbool.h>
#include "strfuncs.h"


size_t string_length(const char *str) {
    unsigned int i = 0;
    size_t length = 0;
    while (str[i] != '\0') {
        length += 1;
        i += 1;
    }
    return length;
}

char * string_filter(const char * str, char c) {
    char *new_str = NULL;
    size_t l_new = 0;
    size_t l = string_length(str);
    
    for (unsigned int i = 0; i <= l; i++){
        if (str[i] != c) {
            l_new += 1;
        }
    }
    
    new_str = malloc(l_new * sizeof(char));
    unsigned int j = 0;
    for (unsigned int i = 0; i <= l; i++) {
        if (str[i]!= c && j <= l_new) {
            new_str[j] = str[i];
            j += 1;
        }
    }
    return new_str;
}