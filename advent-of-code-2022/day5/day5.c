#include "../aoc.h"

#define MAX_LINE_SIZE 40
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
  for (int i=0; i <= s->top; i++) {
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

void solve(char* inputFile, char* part1) {
  FILE* pFile = open_file(inputFile);
  char line[MAX_LINE_SIZE];
  short numStacks = 0;
  bool stacksReady = false;
  CrateStack** stacks;

  while (fgets(line, MAX_LINE_SIZE, pFile) != NULL) {
    // Lines with [] are for constructing the crate stacks.
    if (strchr(line, '[') != NULL) {
      if (!numStacks) {
        numStacks = (strlen(line) / 4);
        stacks = init_all_stacks(numStacks);
      }

      // starting at [1], check every 4th item to get the contents
      printf("%s", line);
      size_t len = strlen(line);
      for (int i=1, j=0; i < (int)len; i+=4, j++) {
        // printf("Pushing c=%c to stack#%d,%d\n", line[i], i, j);
        if (!isspace(line[i]))
          push_crate(line[i], stacks[j]);
      }
      printf("\n");
    }

    // Lines that begin with "move" are the instructions to follow.
    if (strncmp(line, "move", 4) == 0) {
      // Stacks need to be reversed before the move instructions can
      // be executed since they were built from the top down rather
      // than bottom up.
      if (!stacksReady) {
        for (int i = 0; i < numStacks; i++) {
          reverse_crates(stacks[i]);
        }
        stacksReady = true;
      }

      unsigned short nCrates;
      unsigned short iFrom;
      unsigned short iTo;

      sscanf(line, "%*s %hu %*s %hu %*s %hu", &nCrates, &iFrom, &iTo);
      // printf("m %hu f %hu t %hu\n", nCrates, iFrom, iTo);
      for (unsigned short i = 0; i < nCrates; i++) {
        Crate c = pop_crate(stacks[iFrom-1]);
        if (c != '\0')
          push_crate(c, stacks[iTo-1]);
      }
    }
  }

  // temporary:
  strcpy(part1, "abc");
  print_all_stacks(stacks, numStacks);

  free(stacks);
  fclose(pFile);
}

int main(int argc, char** argv) {
  if (argc != 2) {
    puts("[ERROR]: Please specify an input file.");
    exit(EXIT_FAILURE);
  }

  char* part1;
  part1 = (char*)malloc(5 * sizeof(char));
  solve(argv[1], part1);

  printf("Part1 answer: %s\n", part1);
  // printf("Part2 answer: %d\n", part_2);

  free(part1);
  
  return EXIT_SUCCESS;
}