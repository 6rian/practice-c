#include <string.h>
#include "../aoc.h"

#define MAX_LINE_SIZE 55
#define GROUP_SIZE 3

int get_priority(char c) {
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

    // find which character is present in both compartments
    size_t loc = strcspn(left, right);
    char item = left[loc];

    priority_sum += get_priority(item);
  }

  fclose(pFile);
  return priority_sum;
}

int solve_part2(char *input_file) {
  FILE *pFile = open_file(input_file);
  int priority_sum = 0;
  char line[MAX_LINE_SIZE];
  char group[GROUP_SIZE][MAX_LINE_SIZE];
  int count = 0;

  while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
    // add rucksack to the group
    strncpy(group[count++], line, MAX_LINE_SIZE);

    // if the group is full, find the badge
    if (count == GROUP_SIZE) {
      for (int i=0; i < (int)(strlen(group[0]) - 1); i++) {
        char a = group[0][i];
        char *b = strchr(group[1], a);
        char *c = strchr(group[2], a);

        if (b != NULL && c != NULL) {
          priority_sum += get_priority(a);
          break;
        }
      }

      // reset counter to start next group
      count = 0;
    }
  }

  return priority_sum;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  printf("Part1 answer: %d\n", solve(argv[1]));
  printf("Part2 answer: %d\n", solve_part2(argv[1]));
  return EXIT_SUCCESS;
}
