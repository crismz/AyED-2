/*
@file array_helpers.c
@brief Array Helpers method implementation
*/
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "array_helpers.h"

/**
* @brief returns true when reach last entry in flight table
* @return True when is the last entre of the flight table, False otherwise
*/
static bool is_last_line(unsigned int hour, unsigned int type) {
  return  hour == HOURS - 1u && type == TYPE - 1u;
}

void array_dump(DeliveryTable a) {
  for (unsigned int type = 0u; type < TYPE; ++type) {
    for (unsigned int hour = 0u; hour < HOURS; ++hour) {
      Flight f = a[type][hour];
      fprintf(stdout, "%c: flight with %u %s arrived at %u:00", f.code, f.items_amount, f.type == 0 ? "boxes" : "letters", f.hour - 1);
      if (!is_last_line(hour, type))
      {
        fprintf(stdout, "\n");
      }
    }
  }
}

unsigned int extra_space_fee_cost (DeliveryTable a) {
  int i = 19;        // Contador para hacer las horas desde 0 hasta 6pm
  unsigned int j = 0;
  unsigned int boxes = 0;
  unsigned int letters = 0;
  while(i > 0){
    if(a[0][j].hour <= 19){
      boxes+= a[0][j].items_amount;
      if(a[1][j].hour <= 19){
        letters+= a[1][j].items_amount;
      }
      i--;
    } 
    j++;
  }
  unsigned int boxes_cost = 0;
  unsigned int letters_cost = 0;
  if (boxes > MAX_ALLOWED_BOXES){
    boxes_cost = (boxes - MAX_ALLOWED_BOXES) * BOX_PENALTY;
  }
  if (letters > MAX_ALLOWED_LETTERS){
    letters_cost = (letters - MAX_ALLOWED_LETTERS) * LETTER_PENALTY;
  }
  return boxes_cost + letters_cost;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  int i = 0;
  while (!feof(file)) {
    int res = fscanf(file,"_%c_", &code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    Flight flight_boxes = flight_from_file(file,code,boxes);
    Flight flight_letters = flight_from_file(file,code,letters);
  
    array[0][i] = flight_boxes;
    array[1][i] = flight_letters;
    i++;
    fscanf(file,"\n");
  }
  fclose(file);
}
