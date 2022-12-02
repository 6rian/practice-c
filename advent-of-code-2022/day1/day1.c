#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int solve(char *input_file) {
  FILE *pFile = fopen(input_file, "r");
  if (!pFile) {
    perror("[ERROR]");
    exit(EXIT_FAILURE);
  }

  char buffer[10];
  int sum = 0, max = 0;

  while (fgets(buffer, 10, pFile) != NULL) {
    if (strcmp(buffer, "\n") == 0) {
      if (sum > max) max = sum;
      sum = 0;
    } else {
      int calories = atoi(buffer);
      sum += calories;
    }
  }

  // check if the last elf is carried the most
  if (sum > max) max = sum;

  fclose(pFile);
  return max;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  int answer = solve(argv[1]);
  printf("The elf carrying the most is carrying %d calories.\n\n", answer);

  return 0;
}
