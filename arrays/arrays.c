#include <stdlib.h>
#include <stdio.h>

void print_array(int * arr, int len);

void print_array(int * arr, int len) {
  printf("[");
  for (int i=0; i<len; i++) {
    char * trailing_comma = (i == len-1) ? "" : ", ";
    printf("%d%s", arr[i], trailing_comma);
  }
  printf("]\n");
}

int * numbers;

int main(void) {
  numbers = (int *)calloc(2, sizeof(int));

  print_array(numbers, 2);

  free(numbers);
  return 0;
}
