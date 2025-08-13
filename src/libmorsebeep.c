#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <math.h>
#include <ao/ao.h>

static ao_device *a_device = NULL;
static ao_sample_format a_format;
static ao_option *a_option = NULL;
static int a_buf_size;

static char *a_buffer; //The sound

#define UNIT_SHORT 100000
#define UNIT_SHORT_SECOND ((float) UNIT_SHORT / 1000000)
#define UNIT_LONG UNIT_SHORT * 3
#define UNIT_WORD UNIT_SHORT * 7
#define SAMPLE_RATE 44100
#define SAMPLE_SHORT UNIT_SHORT_SECOND * SAMPLE_RATE
#define SAMPLE_LONG SAMPLE_SHORT * 3

void freeBeeper() {
    free(a_buffer);
    ao_close(a_device);
    ao_shutdown();
}

void initBeeper() {
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
    a_format.rate = SAMPLE_RATE;
    a_format.byte_format = AO_FMT_LITTLE;

    ao_append_option(&a_option, "quiet", NULL);

    a_device = ao_open_live(default_driver, &a_format, a_option);
    if (a_device == NULL)
        return;

    a_buf_size = a_format.bits / 4 * a_format.channels * a_format.rate;
    a_buffer = calloc(a_buf_size, sizeof(char));

    for (i = 0; i < a_format.rate; i++) {
        a_sample = (int) (0.75 * 32768.0 * sin(2 * M_PI * freq * ((float) i / a_format.rate)));

        a_buffer[2 * i] = a_buffer[2 * i + 2] = a_sample & 0xff;
        a_buffer[2 * i + 1] = a_buffer[2 * i + 3] = (a_sample >> 8) & 0xff;
    }
}

static void beep(uint_32 duration) {
    ao_play(a_device, a_buffer, duration);
}

void morseBeepCharacter(char x) {
    fputc(x, stdout);
    fflush(stdout);
    switch (x) {
        case '.':
            beep(SAMPLE_SHORT);
            usleep(UNIT_SHORT * 2);
            return;
        case '-':
            beep(SAMPLE_LONG);
            usleep(UNIT_LONG + UNIT_SHORT);
            return;
        case '/':
            usleep(UNIT_WORD);
            return;
        case ' ':
            usleep(UNIT_LONG);
            return;
    }
}

void morseBeep(char *x) {
    while (*x != '\0') {
        morseBeepCharacter(*x);
        x++;
    }
}
