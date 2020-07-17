#include "include/libmorse.h"
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>

char * morseEncode(char * x, int * prosign)
{
	switch (tolower(*x))
	{
	case 'a':
		return ".-";
	case 'b':
		return "-...";
	case 'c':
		return "-.-.";
	case 'd':
		return "-..";
	case 'e':
		return ".";
	case 'f':
		return "..-.";
	case 'g':
		return "--.";
	case 'h':
		return "....";
	case 'i':
		return "..";
	case 'j':
		return ".---";
	case 'k':
		return "-.-";
	case 'l':
		return ".-..";
	case 'm':
		return "--";
	case 'n':
		return "-.";
	case 'o':
		return "---";
	case 'p':
		return ".--.";
	case 'q':
		return "--.-";
	case 'r':
		return ".-.";
	case 's':
		return "...";
	case 't':
		return "-";
	case 'u':
		return "..-";
	case 'v':
		return "...-";
	case 'w':
		return ".--";
	case 'x':
		return "-..-";
	case 'y':
		return "-.--";
	case 'z':
		return "--..";

	//Digits
	case '1':
		return ".----";
	case '2':
		return "..---";
	case '3':
		return "...--";
	case '4':
		return "....-";
	case '5':
		return ".....";
	case '6':
		return "-....";
	case '7':
		return "--...";
	case '8':
		return "---..";
	case '9':
		return "----.";
	case '0':
		return "-----";

	//Punctuation
	case '&':
		return ".-...";

	case '\'':
		return ".----.";

	case '@':
		return ".--.-.";

	case ')':
		return "-.--.-";

	case '(':
		return "-.--.";

	case ':':
		return "---...";

	case ',':
		return "--..--";

	case '=':
		return "-...-";

	case '!':
		return "-.-.--";

	case '.':
		return ".-.-.-";

	case '-':
		return "-....-";

	case '+':
		return ".-.-.";

	case '"':
		return ".-..-.";

	case '?':
		return "..--..";

	case '/':
		return "-..-.";

	//Space
	case ' ':
	case '\n':
		return "/";

	//Prosign Mode
	case '<': *prosign = 1; return "";
	case '>': *prosign = 0; return "";

	//Anything else we have no idea about
	default:
		return "#";
	}
}

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
		}
		case 6:
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
						if(it[3] == '.' && it[4] == '.' && it[5] == '.')
							return ':';
						break;
						case '.': // --.
						switch(it[3])
						{
							case '.': // --..
							switch(it[4])
							{
								case '-': if (it[5] == '-') return ',';
								break;
							}
						}
					}
					case '.': // -.
					switch(it[2])
					{
						case '-': // -.-
						switch(it[3])
						{
							case '-': // -.--
							switch(it[4])
							{
								case '.':
								if(it[5] == '-') return ')';
								break;
							}
							case '.': // -.-.
								if(it[4] == '-' && it[5] == '-')
									return '!';
						}
						case '.':
						if(it[3] == '.' && it[4] == '.' && it[5] == '-')
							return '-';
						break;
					}
				}
				case '.':
				switch (it[1])
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
								case '-': if(it[5] == '.') return '\'';
								break;
							}
							case '.': // .--.
							{
								if(it[5] == '.') return '@';
								break;
							}
						}
						case '.': // .-.
						{
							switch(it[4])
							{
								case '.': if(it[5] == '-') return '.';
							}
						}
					}
					case '.': // ..
					switch(it[3])
					{
						case '-': // ..-
						switch(it[4])
						{
							case '.': if (it[5] == '.') return '?';
							break;
						}
						case '.': // ...
						switch(it[4])
						{
							case '-': if (it[5] == '.') return '"';
							break;
						}
					}
				}
			}
			break;
		}
	}
	return '#';
}

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

#define BIT(var,pos) ((var) & (1<<(pos)))

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

