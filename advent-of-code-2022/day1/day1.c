#include <stdio.h>
#include <stdlib.h>

// int answer(char *input_file);

int solve(char *input_file) {
  puts(input_file);
  return 0;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("Error: please specify an input file.");
  }

  int answer = solve(argv[1]);
  printf("The elf carrying the most is carrying %d calories.\n\n", answer);

  return 0;
}
