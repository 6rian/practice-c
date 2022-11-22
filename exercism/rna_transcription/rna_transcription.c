#include "rna_transcription.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *to_rna(const char *dna) {
    char *rna = (char *)malloc(sizeof(char) * strlen(dna) + 1);
    strcpy(rna, "");

    while (*dna) {
        switch (*dna) {
            case 'G':
                strncat(rna, "C", 2);
                break;
            case 'C':
                strncat(rna, "G", 2);
                break;
            case 'T':
                strncat(rna, "A", 2);
                break;
            case 'A':
                strncat(rna, "U", 2);
                break;
            default:
                continue;
        }
        dna++;
    }

    return rna;
}

int main(void) {
    puts(to_rna("ACGTGGTCTTAA")); // UGCACCAGAAUU
    return 0;
}
