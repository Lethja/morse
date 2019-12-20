#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>

char * morseCompress(char * x)
{
	size_t s = strlen(x);
	size_t c = s / 4;
	int i = 6;
	if(c < 1) c = 1;
	char * r = calloc(c, sizeof(char));
	char * it = r;
	while (*x != '\0')
	{
		if (i < 0)
		{
			it++;
			i = 6;
		}
		switch(*x)
		{
			case ' ':
			default:
				break;
			case '.':
				*it &= ~(1 << i+1);
				*it |= 1 << i;
			break;
			case '-':
				*it |= 1 << i+1;
				*it &= ~(1 << i);
			break;
			case '/':
				*it |= 1 << i+1;
				*it |= 1 << i;
			break;
		}
		i -= 2;
		x++;
	}
	return r;
}

static void morseArg(int argc, char **argv)
{
	char * str = malloc(strlen(argv[1])+1);
	strcpy(str, argv[1]);
	for(int i = 2; i < argc; i++)
	{
		str = realloc(str, strlen(str) + strlen(argv[i]) + 1);
		strcat(str, argv[i]);
	}
	char * m = morseCompress(str);
	fputs(m, stdout);
	free(m);
	fflush(stdout);
}

static void morseBatch(char * str)
{
	char * m = morseCompress(str);
	fputs(m, stdout);
	free(m);
	fflush(stdout);
}

static void morsePipe()
{
	size_t i = 0;
	char t[9];
	t[8] = '\0';
	while((t[i] = fgetc(stdin)) != EOF)
	{
		i++;
		if(i >= 4)
		{
			morseBatch((char *) t);
			i = 0;
			memset((void *) t, '\0', sizeof(char)*8);
			continue;
		}
	}
	if (i > 0)
	{
		t[i+1] = '\0';
		morseBatch((char *) t);
	}
}

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		morseArg(argc, argv);
	}
	else if (isatty(fileno(stdin)))
		printf( "No input\n" );
	else
		morsePipe();
	return 0;
}
