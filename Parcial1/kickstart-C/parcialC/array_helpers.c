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

unsigned int extra_space_fee_cost (DeliveryTable a, unsigned int h) {
  int i = h;           // Contador para la hora
  unsigned int j = 0;           // Contador para referenciar arreglo 
  unsigned int total_cost = 0;  // Costo total
  unsigned int boxes = 0;       // Contador para cajas
  unsigned int letters = 0;       // Contador para cartas
  while(i >= 0){
    if(a[0][j].hour <= h+1){
      boxes = boxes + a[0][j].items_amount;
      letters = letters + a[1][j].items_amount;
      i--;
    }
    j++;
  }
  if(boxes > MAX_ALLOWED_BOXES){
    total_cost = (boxes - MAX_ALLOWED_BOXES) * BOX_PENALTY;
  }  
  if (letters > MAX_ALLOWED_LETTERS){
    total_cost = total_cost + (letters - MAX_ALLOWED_LETTERS) * LETTER_PENALTY;
  }
  
  return total_cost;
}


void array_from_file(DeliveryTable array, const char *filepath) {
  FILE *file = NULL;

  file = fopen(filepath, "r");
  if (file == NULL) {
    fprintf(stderr, "File does not exist.\n");
    exit(EXIT_FAILURE);
  }

  char code;
  unsigned int arrival_hour;
  int i = 0;
  while (!feof(file)) {
    int res = fscanf(file,"_%c_",&code);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    res = fscanf(file,"%u",&arrival_hour);
    if (res != 1) {
      fprintf(stderr, "Invalid file.\n");
      exit(EXIT_FAILURE);
    }
    
    Flight flight_boxes = flight_from_file(file,code,arrival_hour);
    Flight flight_letters = flight_from_file(file,code,arrival_hour);

    array[0][i] = flight_boxes;
    array[1][i] = flight_letters;
    i++;

    fscanf(file,"\n");
  }
  fclose(file);
}
