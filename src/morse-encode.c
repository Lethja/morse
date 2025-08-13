#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "include/libmorse.h"

void morseArg(char *str) {
    int prosign = 0;
    char *stri = str;
    do {
        char *m = morseEncode(stri, &prosign);
        fputs(m, stdout);
        if (!prosign)
            fputc(' ', stdout);
        fflush(stdout);
        stri++;
    } while (*stri != '\0');
}

void morsePipe() {
    char t;
    int prosign = 0;
    while ((t = fgetc(stdin)) != EOF) {
        char *m = morseEncode(&t, &prosign);
        fputs(m, stdout);
        if (!prosign)
            fputc(' ', stdout);
        fflush(stdout);
    }
}

int main(int argc, char **argv) {
    if (argc > 1) {
        int argi = 1;
        do {
            morseArg(argv[argi]);
            argi++;
            if (argi < argc)
                fputs("/ ", stdout);
            else
                break;
        } while (1);
    } else if (isatty(fileno(stdin)))
        printf("No input\n");
    else
        morsePipe();
    putc('\n', stdout);
    return 0;
}
