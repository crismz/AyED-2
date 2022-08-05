/*
  @file main.c
  @brief Main program function implementation
*/
#include <stdio.h>

/** @brief structure which represent a person */
typedef struct _person {
    int age;
    char name_initial;
} person_t;

/**
 * @brief Main program function
 *
 * @return EXIT_SUCCESS when programs executes correctly, EXIT_FAILURE otherwise
 */
int main(void) {

    int x = 1;
    person_t m = {90, 'M'};
    int a[] = {0, 1, 2, 3};
    
    int *xp = NULL;
    person_t *pp = NULL;

    xp = &x;
    *xp = 9;

    xp = &a[1];
    *xp = 42;

    xp = NULL;

    pp = &m;
    pp->age = 100;
    pp->name_initial = 'F';

    pp = NULL;

    
    printf("x = %d\n", x);
    printf("m = (%d, %c)\n", m.age, m.name_initial);
    printf("a[1] = %d\n", a[1]);
}
