#ifndef AOC_H
#define AOC_H

#include <stdio.h>
#include <stdlib.h>

FILE *open_file(char *filename) {
  FILE *pFile = fopen(filename, "r");
  if (!pFile) {
    perror("[ERROR]");
    exit(EXIT_FAILURE);
  }
  return pFile;
}

#endif
