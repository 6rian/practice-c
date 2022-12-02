#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 5

enum point_values {
  LOSE = 0,
  DRAW = 3,
  WIN = 6
};

FILE *open_file(char *filename) {
  FILE *pFile = fopen(filename, "r");
  if (!pFile) {
    perror("[ERROR]");
    exit(EXIT_FAILURE);
  }
  return pFile;
}

int points(char play) {
  switch (play) {
    case 'A':
    case 'X':
      return 1;
    case 'B':
    case 'Y':
      return 2;
    case 'C':
    case 'Z':
      return 3;
    default:
      return 0;
  }
}

bool is_draw(char my_play, char their_play) {
  return (
    (their_play == 'A' && my_play == 'X') ||
    (their_play == 'B' && my_play == 'Y') ||
    (their_play == 'C' && my_play == 'Z')
  ) ? true : false;
}

bool my_win(char my_play, char their_play) {
    switch (my_play) {
      case 'X':
        // rock beats scissors
        if (their_play == 'C') return true;
        break;
      case 'Y':
        // paper beats rock
        if (their_play == 'A') return true;
        break;
      case 'Z':
        // scissors beats paper
        if (their_play == 'B') return true;
        break;
    }
    return false;
}

int solve(char *input_file) {
  FILE *pFile = open_file(input_file);
  int my_score = 0;
  char buffer[MAX_LINE_SIZE];

  while (fgets(buffer, MAX_LINE_SIZE, pFile) != NULL) {
    char their_play = buffer[0];
    char my_play = buffer[2];

    my_score += points(my_play);

    if (is_draw(my_play, their_play)) {
      my_score += DRAW;
      continue;
    }

    if (my_win(my_play, their_play)) my_score += WIN;
  }

  fclose(pFile);
  return my_score;
}

int solve_part2(char *input_file) {
  FILE *pFile = open_file(input_file);
  int my_score = 0;
  char buffer[MAX_LINE_SIZE];

  while (fgets(buffer, MAX_LINE_SIZE, pFile) != NULL) {
    char their_play = buffer[0];
    char desired_outcome = buffer[2];

    switch (their_play) {
      case 'A': // rock
        if (desired_outcome == 'X') my_score += LOSE + points('Z');
        else if (desired_outcome == 'Y') my_score += DRAW + points('X');
        else my_score += WIN + points('Y');
        break;
      case 'B': // paper
        if (desired_outcome == 'X') my_score += LOSE + points('X');
        else if (desired_outcome == 'Y') my_score += DRAW + points('Y');
        else my_score += WIN + points('Z');
        break;
      case 'C': // scissors
        if (desired_outcome == 'X') my_score += LOSE + points('Y');
        else if (desired_outcome == 'Y') my_score += DRAW + points('Z');
        else my_score += WIN + points('X');
    }
  }

  fclose(pFile);
  return my_score;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  int answer = solve(argv[1]);
  printf("My score is: %d\n", answer);

  int answer2 = solve_part2(argv[1]);
  printf("My desired score is: %d\n", answer2);

  return EXIT_SUCCESS;
}
