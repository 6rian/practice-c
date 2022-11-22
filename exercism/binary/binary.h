#ifndef BINARY_H
#define BINARY_H

#define INVALID -1
#define DEBUG 1

#if DEBUG
void debug(const char *input, int expected, int actual);
#endif

int convert(const char *input);

#endif