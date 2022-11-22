#include "binary.h"
#include <stdio.h>
#include <string.h>
#include <math.h>

void debug(const char *input, int expected, int actual) {
    printf("input=%s, expected=%d, actual=%d\n", input, expected, actual);
}

int convert(const char *input) {
    int decimal = 0;
    int length = (int)strlen(input);
    int power = length - 1;
    while (*input) {
        if (*input == '1') {
            decimal += pow(2, power);
        } else if (*input != '0') {
            return INVALID;
        }

        power--;
        input++;
    }

    return decimal;
}

int main(void) {
    debug("0", 0, convert("0"));
    debug("1", 1, convert("1"));
    debug("123", -1, convert("123"));
    debug("100", 9, convert("1001"));
    debug("11010", 26, convert("11010"));
    debug("10001101000", 1128, convert("10001101000"));
    debug("000011111", 31, convert("000011111"));
    debug("10nope", -1, convert("10nope"));

    return 0;
}