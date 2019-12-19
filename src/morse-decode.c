#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

char morseDecode(char * x)
{
	char * it = x;
	char * end = strchr(it, ' ');
	if(end)
		*end = '\0';
	size_t len = strlen(it);
	switch(len)
	{
		case 1:
		switch(*it)
		{
			case '.': return 'E';
			case '-': return 'T';
			case '/': return ' ';
			break;
		}
		case 2:
		{
			switch(*it)
			{
				case '.':
				switch (it[1])
				{
					case '.': return 'I';
					case '-': return 'A';
					break;
				}
				case '-':
				switch (it[1])
				{
					case '.': return 'N';
					case '-': return 'M';
				}
			}
			break;
		}
		case 3:
		{
			switch (*it)
			{
				case '.':
				switch(it[1])
				{
					case '-': // .-
					switch(it[2])
					{
						case '.': return 'R';
						case '-': return 'W';
						break;
					}
					case '.': // ..
					switch(it[2])
					{
						case '.': return 'S';
						case '-': return 'U';
					}
				}
				case '-':
				switch(it[1])
				{
					case '-': // --
					switch(it[2])
					{
						case '.': return 'G';
						case '-': return 'O';
					}
					case '.': // -.
					switch(it[2])
					{
						case '.': return 'D';
						case '-': return 'K';
					}
				}
			}
			break;
		}
		case 4:
		{
			switch (*it)
			{
				case '.':
				switch(it[1])
				{
					case '.': // ..
					switch(it[2])
					{
						case '-': // ..-
							return 'F';
						case '.': // ...
						switch (it[3])
						{
							case '-': return 'V';
							case '.': return 'H';
						}
					}
					case '-': // .-
					switch(it[2])
					{
						case '-': // .--
						switch(it[3])
						{
							case '-': return 'J';
							case '.': return 'P';
						}
						case '.': // .-.
							return 'L';
					}
				}
				case '-':
				switch(it[1])
				{
					case '.': // -.
					switch(it[2])
					{
						case '-': // -.-
						switch(it[3])
						{
							case '-': return 'Y';
							case '.': return 'C';
						}
						case '.': // -..
						switch(it[3])
						{
							case '-': return 'X';
							case '.': return 'B';
						}
					}
					break;
					case '-': // --
					switch(it[2])
					{
						case '.': // --.
						switch(it[3])
						{
							case '-': return 'Q';
							case '.': return 'Z';
						}
					}
				}
			break;
		}
		case 5:
		{
			switch (*it)
			{
				case '-':
				switch (it[1])
				{
					case '-': // --
					switch(it[2])
					{
						case '-': // ---
						switch(it[3])
						{
							case '-': // ----
							switch(it[4])
							{
								case '-': return '0';
								case '.': return '9';
							}
							case '.': // ---.
							if (it[4] == '.') return '8';
						}
						case '.': return '7';
						break;
					}
					case '.': // -.
					switch(it[2])
					{
						case '-':
							if(it[3] == '-' && it[4] == '.')
								return '(';
						break;
						case '.':  // -..
						switch(it[3])
						{
							case '-': if(it[4] == '.') return '/';
							case '.':
							if(it[4] == '.')
								return '6';
							else
								return '=';
						}
					}
				}
				case '.':
				switch(it[1])
				{
					case '-': // .-
					switch(it[2])
					{
						case '-': // .--
						switch(it[3])
						{
							case '-': // .---
							switch(it[4])
							{
								case '-': return '1';
							}
						}
						case '.': // .-.
						switch(it[3])
						{
							case '-': // .-.-
								if(it[4] == '.') return '+';
							case '.': // .-..
								if(it[4] == '.') return '&';
						}
						break;
					}
					case '.':
					switch(it[2])
					{
						case '-':
						switch(it[3])
						{
							case '-':
							switch(it[4])
							{
								case '-': return '2';
							}
						}
						case '.':
						switch(it[3])
						{
							case '-':
							switch(it[4])
							{
								case '-': return '3';
							}
							case '.':
							switch(it[4])
							{
								case '-': return '4';
								case '.': return '5';
							}
						}
					}
				}
			}
			break;
		}/*
		case 6:
		{
			switch (*it)
			{
				switch (*it[1])
				{
					switch(it[2])
					{
						switch(it[3])
						{
							switch(it[4])
							{
								case '-':
									it[5] == '.' ?
										return '' : return '';
								case '.':
									it[5] == '.' ?
										return '' : return '';
							}
						}
					}
				}
			}
			break;*/
		}
	}
	return '#';
}

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
