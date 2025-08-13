#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "include/libmorsebeep.h"

static void morseBeepPipe(FILE *pipe) {
    char t;
    while ((t = fgetc(pipe)) != EOF)
        morseBeepCharacter(t);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        initBeeper();
        int argi = 1;
        do {
            morseBeep(argv[argi]);
            argi++;
            fputc(' ', stdout);
        } while (argi < argc);
        freeBeeper();
    } else if (isatty(fileno(stdin)))
        printf("No input\n");
    else {
        initBeeper();
        morseBeepPipe(stdin);
        freeBeeper();
    }
    putc('\n', stdout);
    return 0;
}
