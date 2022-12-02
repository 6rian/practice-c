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

  // check if the last elf is carrying the most
  if (sum > max) max = sum;

  fclose(pFile);
  return max;
}

int compare(const void *a, const void *b) {
    return (*(int *)b - *(int *)a);
}

int solve_part2(char *input_file) {
  FILE *pFile = fopen(input_file, "r");
  if (!pFile) {
    perror("[ERROR]");
    exit(EXIT_FAILURE);
  }

  char buffer[10];
  int sum = 0;
  int max_sums_length = 2;
  int *sums = (int *)malloc(max_sums_length * sizeof(int));
  int count = 0;

  while (fgets(buffer, 10, pFile) != NULL) {
    if (strcmp(buffer, "\n") == 0) {
      if (count == max_sums_length - 1) {
        max_sums_length += 10;
        sums = (int *)realloc(sums, max_sums_length * sizeof(int));
      }
      sums[count++] = sum;
      sum = 0;
    } else {
      int calories = atoi(buffer);
      sum += calories;
    }
  }

  // don't forget about the last elf
  if(count == max_sums_length -1) {
    max_sums_length += 1;
    sums = (int *)realloc(sums, max_sums_length * sizeof(int));
  }
  sums[count++] = sum;
  
  fclose(pFile);
  qsort(sums, count, sizeof(int), compare);

  int sum_top3 = sums[0] + sums[1] + sums[2];
  free(sums);
  return sum_top3;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  int answer = solve(argv[1]);
  printf("The elf carrying the most is carrying %d calories.\n", answer);

  int answer2 = solve_part2(argv[1]);
  printf("The top 3 elves are carrying a total of %d calories.\n", answer2);

  return 0;
}
