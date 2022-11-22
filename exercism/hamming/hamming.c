#include "hamming.h"
#include <string.h>
#include <stdio.h>

int compute(const char *lhs, const char *rhs) {
    size_t length = strlen(lhs);

    // both sides must be equal length
    if (length != strlen(rhs)) {
        return -1;
    }

    if (strcmp(lhs, rhs) == 0) {
        return 0;
    }

    unsigned int difference = 0;

    for (unsigned int i = 0; i < length; i++) {
        if (lhs[i] != rhs[i]) {
            difference++;
        }
    }

    return difference;
}

int main(void) {
    printf("7=%i\n", compute("GAGCCTACTAACGGGAT", "CATCGTAATGACGGCCT"));
    printf("0=%i\n", compute("", ""));
    printf("0=%i\n", compute("CATG", "CATG"));
    printf("-1=%i\n", compute("AATG", "AAA"));
    printf("1=%i\n", compute("A", "G"));
    return 0;
}