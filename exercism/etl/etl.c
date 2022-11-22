#include "etl.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int compare(const void *a, const void *b) {
    return (((new_map *)a)->key - ((new_map *)b)->key);
}

int convert(const legacy_map *input, const size_t input_len, new_map **output) {

    *output = calloc(26, sizeof(new_map));
    int count = 0;
    
    for (int i=0; i < (int)input_len; i++) {
        size_t keys_len = strlen(input[i].keys);

        for (int k=0; k < (int)keys_len; k++) {
            char key = input[i].keys[k];
            if (isupper(key)) key = tolower(key);

            (*output)[count].key = key;
            (*output)[count++].value = input[i].value;
        }
    }

    qsort(*output, count, sizeof(new_map), compare);
    return count;
}

int main(void) {
    legacy_map input[] = { { 1, "AE" }, { 2, "DG" } };
    int input_len = 2;
    new_map *output = NULL;

    int result_len = convert(input, input_len, &output);
    printf("result_len=%i\n", result_len);

    for (int i=0; i<4; i++) {
        printf("{k:%c, v:%i}\n", output[i].key, output[i].value);
    }

    free(output);
    return 0;
}
