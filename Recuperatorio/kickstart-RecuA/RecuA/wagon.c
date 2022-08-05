/*
@file wagon.c
@brief Implements wagon structure and methods
*/
#include <stdlib.h>
#include "wagon.h"

static const int AMOUNT_OF_WAGON_VARS = 3;

Wagon wagon_from_file(FILE* file)
{
  Wagon wagon;
  char cargoType;

  int res = fscanf(file,EXPECTED_WAGON_LINE_FORMAT,&wagon.number, &cargoType, &wagon.weight);

  if (res != AMOUNT_OF_WAGON_VARS) {
    fprintf(stderr, "Invalid array.\n");
    exit(EXIT_FAILURE);
  }

  if (cargoType == 'r') {
    wagon.cargo = rice;
  } else if (cargoType == 'm') {
    wagon.cargo = mushrooms;
  } else if (cargoType == 'o') {
    wagon.cargo = oatmeal;
  } else if (cargoType == 'p') {
    wagon.cargo = pepper;
  }


  return wagon;
}
