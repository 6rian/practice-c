#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "armstrong_numbers.h"

char number_as_string[10];

/* convert int to string */
void number_to_string(int number, char *str) {
    sprintf(str, "%d", number);
}

/* count the digits of a number string */
int count_digits(char *numberString) {
    for (int i=0; i<9; i++) {
        if (numberString[i] == 0) {
            return i;
            break;
        }
    }
    return 0;
}

bool is_armstrong_number(int candidate) {
    number_to_string(candidate, number_as_string);
    int digits = count_digits(number_as_string);
    
    int sum = 0;
    for (int i=0; i<digits; i++) {
        // convert character digit back to an int
        int x = number_as_string[i] - '0';
        sum += pow(x, digits);
    }
    return (sum == candidate) ? true : false;
}

int main(void) {
  printf("n=%i, expected=%i, actual=%i\n", 153, true, is_armstrong_number(153));
  printf("n=%i, expected=%i, actual=%i\n", 0, true, is_armstrong_number(0));
  printf("n=%i, expected=%i, actual=%i\n", 9475, false, is_armstrong_number(9475));
  printf("n=%i, expected=%i, actual=%i\n", 100, false, is_armstrong_number(100));
  printf("n=%i, expected=%i, actual=%i\n", 9926315, true, is_armstrong_number(9926315));
  printf("n=%i, expected=%i, actual=%i\n", 9926314, false, is_armstrong_number(9926314));
  return 0;
}
