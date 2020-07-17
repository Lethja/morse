#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "include/libmorse.h"

static void morseArg(char * str)
{
	char * stri = str;
	char t[7];
	t[7] = '\0';
	size_t i = 0;
	do
	{
		if (*stri == ' ' || *stri == '\0' || i == 6)
		{
			t[i] = '\0';
			char m = morseDecode((char *) t);
			fputc(m, stdout);
			fflush(stdout);
			i = 0;
			if (*stri == ' ')
				*stri++;
			else
				break;
		}

		t[i] = *stri;
		stri++;
		i++;
	} while (1);
}

static void morsePipe()
{
	char t[7];
	t[7] = '\0';
	size_t i = 0;
	while((t[i] = fgetc(stdin)) != EOF)
	{
		if (t[i] == ' ' || i == 6)
		{
			t[i] = '\0';
			char m = morseDecode((char *) t);
			fputc(m, stdout);
			fflush(stdout);
			i = 0;
			continue;
		}
		i++;
	}
}

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		int argi = 1;
		do
		{
			morseArg(argv[argi]);
			argi++;
			if(argi >= argc)
				break;
		} while (1);
	}
	else if (isatty(fileno(stdin)))
		printf( "No input\n" );
	else
		morsePipe();
	putc('\n', stdout);
	return 0;
}
