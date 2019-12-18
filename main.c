#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <ao/ao.h>

static ao_device * a_device = NULL;
static ao_sample_format a_format;
static ao_option * a_option = NULL;
static int a_buf_size;

static char * a_buffer; //The sound

#define WORD_BREAK 200000
#define CHAR_BREAK 100000
#define MORSE_LONG 22050
#define MORSE_SHORT 11025

void freeSound()
{
	free(a_buffer);
	ao_close(a_device);
	ao_shutdown();
}

void initSound()
{
	int default_driver;
	size_t buf_size;
	int a_sample;
	float freq = 550.0;
	int i;
	
	ao_initialize();
	default_driver = ao_default_driver_id();
	
	memset(&a_format, 0, sizeof(a_format));
	a_format.bits = 16;
	a_format.channels = 1;
	a_format.rate = 44100;
	a_format.byte_format = AO_FMT_LITTLE;
	
	ao_append_option(&a_option, "quiet", NULL);
	
	a_device = ao_open_live(default_driver, &a_format, a_option);
	if (a_device == NULL) 
		return;
		
	a_buf_size = a_format.bits/4 * a_format.channels * a_format.rate;
	a_buffer = calloc(a_buf_size, sizeof(char));
	
	for (i = 0; i < a_format.rate; i++) 
	{
		a_sample = (int)(0.75 * 32768.0 *
			sin(2 * M_PI * freq * ((float) i/a_format.rate)));

		a_buffer[2*i] = a_buffer[2*i+2] = a_sample & 0xff;
		a_buffer[2*i+1] = a_buffer[2*i+3] = (a_sample >> 8) & 0xff;
	}
}

static void beep(size_t duration)
{
	ao_play(a_device, a_buffer, duration);
}

void morseBeepc(char x)
{
	fputc(x, stdout);
	fflush(stdout);
	switch (x)
	{
		case '.':
			beep(MORSE_SHORT);
		break;
		case '-':
			beep(MORSE_LONG);
		break;
		case '/':
			usleep(WORD_BREAK);
		break;
		case ' ':
			usleep(CHAR_BREAK);
		break;
	}
	usleep(CHAR_BREAK);
}

void morseBeep(char * x)
{
	while (*x != '\0')
	{
		morseBeepc(*x);
		x++;
	}
}

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
	case ' ':
		return "/ ";
	default:
		return "";
	}
}

void morseArg(char * str)
{
	char * stri = str;
	do
	{
		char * m = morseEncode(stri);
		/*fputs(m, stdout);
		fflush(stdout);*/
		morseBeep(m);
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
		morseBeep(m);
	}
}

int main(int argc, char **argv)
{
	if(argc > 1)
	{
		initSound();
		int argi = 1;
		do
		{
			morseArg(argv[argi]);
			argi++;
			if(argi < argc)
			{
				fputs("/ ", stdout);
				usleep(WORD_BREAK);
			}
			else
				break;
		} while (1);
	}
	else if (isatty(fileno(stdin)))
		printf( "No input\n" );
	else
	{
		initSound();
		morsePipe();
	}
	putc('\n', stdout);
	if(a_device)
		freeSound();
	return 0;
}
