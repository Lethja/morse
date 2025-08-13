#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include "include/libmorse.h"

static void morseStrTrim(char *x) {
    char *ls = strrchr(x, ' ');
    char *si = ls;
    size_t l = strlen(x);
    if (ls - x == l - 1) {
        si--;
        for (size_t i = x - si; i > 0; i--) {
            if (*si != ' ') {
                si++;
                *si = '\0';
                return;
            }
            si--;
        }
    }
}

static void morsePipe() {
    size_t i = 0;
    char t;
    char *p = calloc(1, sizeof(char));
    while ((t = fgetc(stdin)) != EOF) {
        char *m = morseUncompress(t);
        p = realloc(p, strlen(p) + strlen(m) + 1);
        strcat(p, m);
    }

    /* Since compression works by putting storing 4 units in a byte
     * it is very likely that we have some trailing spaces at the end
     * of extraction. This function will Remove trailing spaces from
     * the output if nessacary
     */
    morseStrTrim(p);

    fputs(p, stdout);
    free(p);
    fputs(" \n", stdout);
    fflush(stdout);
}

int main(int argc, char **argv) {
    if (!isatty(fileno(stdin))) {
        morsePipe();
        return 0;
    } else {
        printf("Please pipe your compressed data to uncompress it\n");
        return 1;
    }
}
