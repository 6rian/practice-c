#ifndef ARMSTRONG_NUMBERS_H
#define ARMSTRONG_NUMBERS_H

#include <stdbool.h>

int count_digits(char *str);
void number_to_string(int number, char *str);
bool is_armstrong_number(int candidate);

#endif
