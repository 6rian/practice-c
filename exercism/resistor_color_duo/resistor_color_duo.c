#include "resistor_color_duo.h"
#include <stdio.h>
#include <stdlib.h>

void debug(int expected, int actual) {
    printf("expected=%d, actual=%d\n", expected, actual);
}

int color_code(resistor_band_t colors[]) {
    int MAX_COLORS = 2;
    char *codes = (char *)malloc(2 * sizeof(int));

    for (int i=0; i<MAX_COLORS; i++) {
        switch (colors[i]) {
            case BLACK:
            case BROWN:
            case RED:
            case ORANGE:
            case YELLOW:
            case GREEN:
            case BLUE:
            case VIOLET:
            case GREY:
            case WHITE:
                codes[i] = '0' + colors[i];
                break;
            default:
                continue;
        }
    }

    return atoi(codes);
}

int main(void) {
    debug(10, color_code((resistor_band_t[]){BROWN, BLACK}));
    debug(33, color_code((resistor_band_t[]){ORANGE, ORANGE}));
    debug(51, color_code((resistor_band_t[]){GREEN, BROWN, ORANGE}));
    debug(1, color_code((resistor_band_t[]){BLACK, BROWN}));
    return 0;
}
