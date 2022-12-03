#include <string.h>
#include "../aoc.h"

#define MAX_LINE_SIZE 55

int points(char c) {
  if (c >= 97 && c <= 122) {
    return c - 96;
  }
  return c - 38;
}

int solve(char *input_file) {
  FILE *pFile = open_file(input_file);
  int priority_sum = 0;
  char line[MAX_LINE_SIZE];

  while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
    // split into 2 compartments
    int length = (int)strlen(line) - 1;
    int middle = length / 2;
    char *left = (char *)calloc(middle + 1, sizeof(char));
    char *right = (char *)calloc(middle + 1, sizeof(char));
    strncpy(left, line, middle);
    strncpy(right, line + middle, middle);
    // printf("length=%d, middle=%d, left=%s, right=%s, line=%s", length, middle, left, right, line);

    // find which character is present in both compartments
    size_t loc = strcspn(left, right);
    char item = left[loc];
    // printf("loc=%d, char=%c, left=%s, right=%s\n", (int)loc, item, left, right);

    priority_sum += points(item);
    printf("loc=%d, char=%c, points=%d, left=%s, right=%s\n", (int)loc, item, points(item), left, right);
  }

  fclose(pFile);
  return priority_sum;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  int answer = solve(argv[1]);
  printf("Part1 answer: %d\n", answer);

  return EXIT_SUCCESS;
}
