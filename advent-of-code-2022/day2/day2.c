#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_LINE_SIZE 5

enum outcome_values {
  LOSE = 0,
  DRAW = 3,
  WIN = 6
};

typedef struct moves {
  char ROCK;
  char PAPER;
  char SCISSORS;
} moves;

typedef struct outcomes {
  char LOSE;
  char DRAW;
  char WIN;
} possible_outcomes;

const moves my_moves = {'X', 'Y', 'Z'};
const moves their_moves = {'A', 'B', 'C'};
const possible_outcomes outcomes = {'X', 'Y', 'Z'};

FILE *open_file(char *filename) {
  FILE *pFile = fopen(filename, "r");
  if (!pFile) {
    perror("[ERROR]");
    exit(EXIT_FAILURE);
  }
  return pFile;
}

int points(char play) {
  if (play == my_moves.ROCK || play == their_moves.ROCK) return 1;
  if (play == my_moves.PAPER || play == their_moves.PAPER) return 2;
  if (play == my_moves.SCISSORS || play == their_moves.SCISSORS) return 3;
  return 0;
}

bool is_draw(char my_play, char their_play) {
  return (
    (their_play == their_moves.ROCK && my_play == my_moves.ROCK) ||
    (their_play == their_moves.PAPER && my_play == my_moves.PAPER) ||
    (their_play == their_moves.SCISSORS && my_play == my_moves.SCISSORS)
  ) ? true : false;
}

bool my_win(char my_play, char their_play) {
  return (
    (my_play == my_moves.ROCK && their_play == their_moves.SCISSORS) ||
    (my_play == my_moves.PAPER && their_play == their_moves.ROCK) ||
    (my_play == my_moves.SCISSORS && their_play == their_moves.PAPER)
  ) ? true : false;
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

    if (their_play == their_moves.ROCK) {
      if (desired_outcome == outcomes.LOSE) my_score += LOSE + points(my_moves.SCISSORS);
      else if (desired_outcome == outcomes.DRAW) my_score += DRAW + points(my_moves.ROCK);
      else my_score += WIN + points(my_moves.PAPER);
      continue;
    }

    if (their_play == their_moves.PAPER) {
      if (desired_outcome == outcomes.LOSE) my_score += LOSE + points(my_moves.ROCK);
      else if (desired_outcome == outcomes.DRAW) my_score += DRAW + points(my_moves.PAPER);
      else my_score += WIN + points(my_moves.SCISSORS);
      continue;
    }

    if (their_play == their_moves.SCISSORS) {
      if (desired_outcome == outcomes.LOSE) my_score += LOSE + points(my_moves.PAPER);
      else if (desired_outcome == outcomes.DRAW) my_score += DRAW + points(my_moves.SCISSORS);
      else my_score += WIN + points(my_moves.ROCK);
      continue;
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
