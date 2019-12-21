#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>

#define BIT(var,pos) ((var) & (1<<(pos)))

static void morseStrTrim(char * x)
{
	char * ls = strrchr(x, ' ');
	char * si = ls;
	size_t l = strlen(x);
	if(ls - x == l-1)
	{
		si--;
		for (size_t i = x - si; i > 0; i--)
		{
			if (*si != ' ')
			{
				si++;
				*si = '\0';
				return;
			}
			si--;
		}
	}
}

char * morseUncompress(char x)
{
	if(x == '\0')
		return "";
	char * r = malloc(5);
	r[4] = '\0';
	size_t it = 0;
	for(char i = 7; i >= 0; i -= 2)
	{
		if(BIT(x,i) > 0)
		{
			if(BIT(x,i - 1) > 0)
				r[it] = '/';
			else
				r[it] = '-';
		}
		else if(BIT(x,i - 1) > 0)
			r[it] = '.';
		else
			r[it] = ' ';
		it++;
	}
	return r;
}

static void morsePipe()
{
	size_t i = 0;
	char t;
	char * p = calloc(1, sizeof(char));
	while((t = fgetc(stdin)) != EOF)
	{
		char * m = morseUncompress(t);
		p = realloc(p, strlen(p)+strlen(m)+1);
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

int main(int argc, char ** argv)
{
	if (!isatty(fileno(stdin)))
	{
		morsePipe();
		return 0;
	}
	else
	{
		printf( "Please pipe your compressed data to uncompress it\n" );
		return 1;
	}
}
