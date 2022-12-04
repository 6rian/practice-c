#ifndef AOC_H
#define AOC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>

FILE *open_file(char *filename) {
  FILE *pFile = fopen(filename, "r");
  if (!pFile) {
    perror("[ERROR]");
    exit(EXIT_FAILURE);
  }
  return pFile;
}

void green() {
  printf("\033[0;32m");
}

void red() {
  printf("\033[0;31m");
}

void reset_color() {
  printf("\033[0m");
}

#endif
