#include "raindrops.h"
#include <stdio.h>
#include <string.h>

char *convert(char result[], int drops) {
    if ((drops % 3) == 0) {
        strcat(result, "Pling");
    }
    if ((drops % 5) == 0) {
        strcat(result, "Plang");
    }
    if ((drops % 7) == 0) {
        strcat(result, "Plong");
    }

    if (!*result) {
        sprintf(result, "%i", drops);
    }

    return result;
}

int main(void) {
    char result[16] = {0};
    printf("%i, %s=%s\n", 30, "PlingPlang", convert(result, 30));

    char result1[16] = {0};
    printf("%i, %s=%s\n", 28, "Plong", convert(result1, 28));

    char result2[16] = {0};
    printf("%i, %s=%s\n", 34, "34", convert(result2, 34));

    char result3[16] = {0};
    printf("%i, %s=%s\n", 21, "PlingPlong", convert(result3, 21));
    return 0;
}
