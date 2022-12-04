#include "../aoc.h"

#define MAX_LINE_SIZE 15

void parse_line(char* line, uint16_t* sections) {
  uint16_t count = 0;
  const char* delimiters = "-,";
  char* token;
  token = strtok(line, delimiters);

  while (token != NULL && count < 4) {
    sections[count++] = (uint16_t)atoi(token);
    token = strtok(NULL, delimiters);
  }
}

bool in_set(uint16_t n, uint16_t min, uint16_t max) {
  return (n >= min && n <= max) ? true : false;
}

bool has_overlap(uint16_t* sections) {
  short a = sections[0];
  short b = sections[1];
  short c = sections[2];
  short d = sections[3];
  if (in_set(a, c, d) && in_set(b, c, d)) return true;
  if (in_set(c, a, b) && in_set(d, a, b)) return true;
  return false;
}

uint16_t solve(char* input_file) {
  FILE* pFile = open_file(input_file);
  int overlap = 0;
  char line[MAX_LINE_SIZE];

  while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
    uint16_t sections[4];
    parse_line(line, sections);
    if (has_overlap(sections)) overlap += 1;
  }

  fclose(pFile);
  return overlap;
}

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  printf("Part1 answer: %d\n", solve(argv[1]));
  // printf("Part2 answer: %d\n", solve_part2(argv[1]));
  return EXIT_SUCCESS;
}
