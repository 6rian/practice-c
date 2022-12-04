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

bool has_overlap(bool full, uint16_t* sections) {
  uint16_t a = sections[0];
  uint16_t b = sections[1];
  uint16_t c = sections[2];
  uint16_t d = sections[3];

  if (full) {
    if (
      (in_set(a, c, d) && in_set(b, c, d)) ||
      (in_set(c, a, b) && in_set(d, a, b))
    ) return true;
  } else {
    if (
      (in_set(a, c, d) || in_set(b, c, d)) ||
      (in_set(c, a, b) || in_set(d, a, b))
    ) return true;
  }

  return false;
}

bool has_full_overlap(uint16_t* sections) {
  return has_overlap(true, sections);
}

bool has_partial_overlap(uint16_t* sections) {
  return has_overlap(false, sections);
}

void solve(
  char* input_file,
  uint16_t* full_overlap,
  uint16_t* partial_overlap
) {
  FILE* pFile = open_file(input_file);
  char line[MAX_LINE_SIZE];

  while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
    uint16_t sections[4];
    parse_line(line, sections);

    if (has_full_overlap(sections)) {
      *full_overlap += 1;
      *partial_overlap += 1;
    } else {
      if (has_partial_overlap(sections)) *partial_overlap += 1;
    }
  }

  fclose(pFile);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  uint16_t part_1 = 0;
  uint16_t part_2 = 0;
  solve(argv[1], &part_1, &part_2);

  printf("Part1 answer: %d\n", part_1);
  printf("Part2 answer: %d\n", part_2);
  return EXIT_SUCCESS;
}
