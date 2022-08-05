/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"
#include "wagon.h"

char * cargo_type_to_str(cargo_t cargo) {
  if (cargo == rice)
    return "rice";
  if (cargo == mushrooms)
    return "mushrooms";
  if (cargo == oatmeal)
    return "oatmeal";
  if (cargo == pepper)
    return "pepper";
  return "error";
}

void array_dump(Train t, unsigned int size) {
  for (unsigned int i = 0u; i < size; ++i) {
    Wagon w = t[i];
    fprintf(stdout, "wagon %u: %u kg of %s", w.number, w.weight, cargo_type_to_str(w.cargo));
    if (i != size-1) {
      fprintf(stdout, "\n");
    }
  }
}

unsigned int discarded_wagons (Train t, unsigned int size) {
  unsigned int wagons_discarded = 0;        // Variable donde guarda los vagones descartados
  unsigned int wagons_contiguos = 0;        // Variable donde que guarda la cantidad de vagones seguidos de oatmeal
  for(unsigned int i = 0; i < size; i++){
    if(t[i].cargo == oatmeal){
      wagons_contiguos++;
      if(wagons_contiguos > 2){
        wagons_discarded++;
      }
    } else {
      wagons_contiguos = 0;
    }
  }
  return wagons_discarded;
}

// the wagon data should be saved on array
// the number of wagons should be stored on trainSize
void array_from_file(Train array, unsigned int * trainSize, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  unsigned int size = 0;
  unsigned int totalKg = 0;

  int res = fscanf(file,"<%c> %u %u",&code, trainSize, &totalKg);
  if (res != 3) {
    fprintf(stderr, "Invalid file.\n");
    exit(EXIT_FAILURE);
  }

  size = *trainSize;
  if (size > MAX_SIZE) {
    fprintf(stderr, "The size is more than MAX_SIZE .\n");
    exit(EXIT_FAILURE);
  }
    
  while (size > 0) {
    Wagon wagon = wagon_from_file(file);
    array[wagon.number-1] = wagon;
    size--;
  }
  fclose(file);
}
