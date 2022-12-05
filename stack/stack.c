#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define STACK_SIZE 5

typedef struct char_stack {
  char* data;
  int top;
} char_stack_t;

void init_stack(char_stack_t* s) {
  s->data = (char*)calloc(STACK_SIZE, sizeof(char));
  s->top = -1;
}

bool is_empty(char_stack_t* s) {
  return (s->top == -1) ? true : false;
}

bool is_full(char_stack_t* s) {
  return (s->top == STACK_SIZE - 1) ? true : false;
}

void push(char c, char_stack_t* s) {
  if (is_full(s)) {
    puts("ERROR: STACK IS FULL!");
    return;
  }

  s->top++;
  s->data[s->top] = c;
}

char pop(char_stack_t* s) {
  if (is_empty(s)) {
    puts("ERROR: STACK IS EMPTY");
    return '\0';
  }

  return s->data[s->top--];
}

void dump_stack(char_stack_t* s) {
  for (int i=0; i <= s->top; i++) {
    printf("%c\n", s->data[i]);
  }
}

int main (void) {
  char_stack_t myStack;
  init_stack(&myStack);

  assert(is_empty(&myStack));
  push('6', &myStack);
  push('r', &myStack);
  push('i', &myStack);
  push('a', &myStack);
  push('n', &myStack);
  assert(!is_empty(&myStack));
  dump_stack(&myStack);

  // stack is full
  push('!', &myStack);
  
  char c = pop(&myStack);
  assert(c == 'n');
  printf("popped=%c\n", c);
  assert(myStack.top == 3);
  dump_stack(&myStack);


  pop(&myStack);
  pop(&myStack);
  pop(&myStack);
  pop(&myStack);
  assert(is_empty(&myStack));

  char empty = pop(&myStack);
  assert(empty == '\0');

  free(myStack.data);
  return 0;
}