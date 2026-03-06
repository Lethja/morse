#ifndef LIB_MORSE
#define LIB_MORSE

char *morseCompress(char *x);

char *morseUncompress(char x);

char *morseEncode(char *x, int *prosign);

char morseDecode(char *x);

#endif /* LIB_MORSE */