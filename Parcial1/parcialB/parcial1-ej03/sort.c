/*
  @file sort.c
  @brief sort functions implementation
*/
#include <stdbool.h>
#include <assert.h>
#include "helpers.h"
#include "sort.h"
#include "movie.h"


bool goes_before(movie_t s1, movie_t s2) {
    bool res = s1.runtime <= s2.runtime;
    return res;
}

unsigned int array_sorted_until(movie_t movielist[], unsigned int size) {
  unsigned int i = 0;
  bool sorted = true;
  if (size == 0) {
    return 0;
  } 
  while (sorted && i < size-1) {
    if (movielist[i].runtime <= movielist[i+1].runtime) {
      sorted = true;
      i++;
    } else {
      sorted = false;
    }
  }
  return i;
}

