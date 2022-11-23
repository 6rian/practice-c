#include "nucleotide_count.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *count(const char *dna_strand) {
    int a = 0, c = 0, t = 0, g = 0;
    char *result = (char *)malloc(32 * sizeof(char));

    while (*dna_strand) {
        switch (*dna_strand) {
            case 'A':
                a++;
                break;
            case 'C':
                c++;
                break;
            case 'G':
                g++;
                break;
            case 'T':
                t++;
                break;
            default:
                // invalid
                strcpy(result, "");
                return result;
        }
        dna_strand++;
    }
    
    sprintf(result, "A:%i C:%i G:%i T:%i", a, c, g, t);
    return result;
}

int main(void) {
    // invalid
    puts(count("ABC"));

    // A:20 C:12 G:17 T:21
    puts(count("AGCTTTTCATTCTGACTGCAACGGGCAATATGTCTCTGTGTGGATTAAAAAAAGAGTGTCTGATAGCAGC"));

    return 0;
}
