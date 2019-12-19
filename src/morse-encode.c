#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char * morseEncode(char * x)
{
	switch (tolower(*x))
	{
	case 'a':
		return ".- ";
	case 'b':
		return "-... ";
	case 'c':
		return "-.-. ";
	case 'd':
		return "-.. ";
	case 'e':
		return ". ";
	case 'f':
		return "..-. ";
	case 'g':
		return "--. ";
	case 'h':
		return ".... ";
	case 'i':
		return ".. ";
	case 'j':
		return ".--- ";
	case 'k':
		return "-.- ";
	case 'l':
		return ".-.. ";
	case 'm':
		return "-- ";
	case 'n':
		return "-. ";
	case 'o':
		return "--- ";
	case 'p':
		return ".--. ";
	case 'q':
		return "--.- ";
	case 'r':
		return ".-. ";
	case 's':
		return "... ";
	case 't':
		return "- ";
	case 'u':
		return "..- ";
	case 'v':
		return "...- ";
	case 'w':
		return ".-- ";
	case 'x':
		return "-..- ";
	case 'y':
		return "-.-- ";
	case 'z':
		return "--.. ";

	//Digits
	case '1':
		return ".---- ";
	case '2':
		return "..--- ";
	case '3':
		return "...-- ";
	case '4':
		return "....- ";
	case '5':
		return "..... ";
	case '6':
		return "-.... ";
	case '7':
		return "--... ";
	case '8':
		return "---.. ";
	case '9':
		return "----. ";
	case '0':
		return "----- ";

	//Punctuation
	case '&':
		return ".-... ";

	case '\'':
		return ".----. ";

	case '@':
		return ".--.-. ";

	case ')':
		return "-.--.- ";

	case '(':
		return "-.--. ";

	case ':':
		return "---... ";

	case ',':
		return "--..-- ";

	case '=':
		return "-...- ";

	case '!':
		return "-.-.-- ";

	case '.':
		return ".-.-.- ";

	case '-':
		return "-....- ";

	case '+':
		return ".-.-. ";

	case '"':
		return ".-..-. ";

	case '?':
		return "..--.. ";

	case '/':
		return "-..-. ";

	//Space
	case ' ':
		return "/ ";
	default:
		return "#";
	}
}

void morseArg(char * str)
{
	char * stri = str;
	do
	{
		char * m = morseEncode(stri);
		fputs(m, stdout);
		fflush(stdout);
		stri++;
	}
	while (*stri != '\0');
}

void morsePipe()
{
	char t;
	while((t = fgetc(stdin)) != EOF)
	{
		char * m = morseEncode(&t);
		fputs(m, stdout);
		fflush(stdout);
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
			if(argi < argc)
				fputs("/ ", stdout);
			else
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
