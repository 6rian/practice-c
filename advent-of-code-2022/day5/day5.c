#include "../aoc.h"

#define MAX_LINE_SIZE 40
#define MAX_STACKS 9
#define INITIAL_CRATE_STACK_SIZE 10

typedef char Crate;

typedef struct CrateStack {
  Crate* crates;
  int size;
  int top;
} CrateStack;

CrateStack* create_stack_of_length(int n) {
  CrateStack* s = (CrateStack *)malloc(sizeof(CrateStack));
  s->crates = (Crate*)malloc(sizeof(Crate) * n);
  s->size = n;
  s->top = -1;
  return s;
}

CrateStack* create_stack() {
  return create_stack_of_length(INITIAL_CRATE_STACK_SIZE);
}

bool is_stack_empty(CrateStack* s) {
  return (s->top == -1) ? true : false;
}

bool is_stack_full(CrateStack* s) {
  return (s->top == s->size - 1) ? true : false;
}

void extend_stack(CrateStack *s) {
  int newSize = s->size + INITIAL_CRATE_STACK_SIZE;
  Crate* old = s->crates;
  Crate* new = (Crate*)malloc(newSize * sizeof(Crate));
  for (int i = 0; i <= s->top; i++) {
    new[i] = s->crates[i];
  }

  s->size = newSize;
  s->crates = new;
  free(old);
}

void push_crate(Crate c, CrateStack* s) {
  if (is_stack_full(s)) {
    extend_stack(s);
  }
  s->top++;
  s->crates[s->top] = c;
}

Crate pop_crate(CrateStack* s) {
  if (is_stack_empty(s)) {
    return '\0';
  }
  return s->crates[s->top--];
}

void print_stack(CrateStack* s) {
  if (is_stack_empty(s)) {
    puts("Stack is empty");
    return;
  }
  for (int i = 0; i <= s->top; i++) {
    printf("[%c] ", s->crates[i]);
  }
  printf("\n");
}

void print_all_stacks(CrateStack** stacks, int length) {
  for (int i = 0; i < length; i++) {
    print_stack(stacks[i]);
  }
}

CrateStack** init_all_stacks(int n) {
  CrateStack** stacks = (CrateStack**)malloc(
    n * sizeof(CrateStack)
  );
  for (int i = 0; i < n; i++) {
    stacks[i] = create_stack();
  }
  return stacks;
}

void destroy_all_stacks(CrateStack** stacks, int length) {
  for (int i = 0; i < length; i++) {
    free(stacks[i]->crates);
    free(stacks[i]);
  }
}

void reverse_crates(CrateStack* s) {
  if (is_stack_empty(s)) return;
  int left = 0;
  int right = s->top;
  while (right > left) {
    int tmp = s->crates[right];
    s->crates[right] = s->crates[left];
    s->crates[left] = tmp;
    left++;
    right--;
  }
}

bool is_stack_construction(char* line) {
  // Lines with [] are for constructing the crate stacks.
  return (strchr(line, '[') != NULL) ? true : false;
}

bool is_move_instruction(char* line) {
  // Lines that begin with "move" are the instructions to follow.
  return (strncmp(line, "move", 4) == 0) ? true : false;
}

void get_tops_of_stacks(char* dest, CrateStack** stacks, int numStacks) {
  for (int i = 0; i < numStacks; i++) {
    char* c = (char*)malloc(2 * sizeof(char));
    sprintf(c, "%c", stacks[i]->crates[stacks[i]->top]);
    strncat(dest, c, 1);
    free(c);
  }
}

void solve(char* inputFile, char* partOneTops, char* partTwoTops) {
  FILE* pFile = open_file(inputFile);
  char line[MAX_LINE_SIZE];
  short numStacks = 0;
  bool stacksReady = false;
  CrateStack** partOneStacks;
  CrateStack** partTwoStacks;

  while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
    if (is_stack_construction(line)) {
      if (!numStacks) {
        numStacks = (strlen(line) / 4);
        partOneStacks = init_all_stacks(numStacks);
        partTwoStacks = init_all_stacks(numStacks);
      }

      // Every 4th item that isn't a space is a crate, to be added to
      // its respective stack
      for (int i=1, j=0; i < (int)strlen(line); i+=4, j++) {
        if (!isspace(line[i])) {
          push_crate(line[i], partOneStacks[j]);
          push_crate(line[i], partTwoStacks[j]);
        }
      }
    }
    
    if (is_move_instruction(line)) {
      // Stacks need to be reversed before the move instructions can
      // be executed since they were built from the top down rather
      // than bottom up.
      if (!stacksReady) {
        for (int i = 0; i < numStacks; i++) {
          reverse_crates(partOneStacks[i]);
          reverse_crates(partTwoStacks[i]);
        }
        stacksReady = true;
      }

      unsigned short nCrates;
      unsigned short iFrom;
      unsigned short iTo;

      sscanf(line, "%*s %hu %*s %hu %*s %hu",
        &nCrates,
        &iFrom,
        &iTo
      );
      for (unsigned short i = 0; i < nCrates; i++) {
        // Part 1: move one crate at a time
        Crate c = pop_crate(partOneStacks[iFrom - 1]);
        if (c != '\0') push_crate(c, partOneStacks[iTo - 1]);

        // Part 2: move crates in bulk
        // create temp stack
        // pop items and push to temp
        // reverse temp
        // until temp is empty, pop items and push to destination
        // free(temp)
      }
    }
  }

  // Finish by getting the top crate from each stack
  get_tops_of_stacks(partOneTops, partOneStacks, numStacks);
  // TEMP:
  strcpy(partTwoTops, "..todo");

  destroy_all_stacks(partOneStacks, numStacks);
  destroy_all_stacks(partTwoStacks, numStacks);
  fclose(pFile);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  // char* part1 = solve(argv[1]);
  char* part1 = (char*)malloc((MAX_STACKS + 1) * sizeof(char));
  char* part2 = (char*)malloc((MAX_STACKS + 1) * sizeof(char));
  solve(argv[1], part1, part2);

  printf("Part1 answer: %s\n", part1);
  printf("Part2 answer: %s\n", part2);

  return EXIT_SUCCESS;
}
