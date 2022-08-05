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
  unsigned int j;                           // Variable para encontrar el vagon numero i, ya que no necesariamente esta ordenado por número de vagones
  bool is_wagon_number;                     // Bool para cuando se encuntre el vagon i
  for(unsigned int i = 1; i < size+1; i++){
    is_wagon_number = false;
    j = 0;                                  // Se inicializa cada ciclo de for para encontrar el vagon numero i

    while(j < size && !is_wagon_number){    
      if(t[j].number == i){
        is_wagon_number = true;
      } else {
        j++;
      }
    }

    if(t[j].cargo == oatmeal){
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

  unsigned int i = 0;
  while (size > 0) {
    Wagon wagon = wagon_from_file(file);
    array[i] = wagon;
    i++;
    size--;
  }
  fclose(file);
}

