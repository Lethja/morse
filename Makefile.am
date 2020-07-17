bin_PROGRAMS = morse-audio morse-compress morse-decode morse-encode morse-uncompress

lib_LTLIBRARIES = libmorse.la
libmorse_la_SOURCES = src/libmorse.c include/libmorse.h

morse_audio_SOURCES = src/morse-audio.c

morse_compress_SOURCES = src/morse-compress.c include/libmorse.h
morse_compress_LDADD = libmorse.la

morse_decode_SOURCES = src/morse-decode.c include/libmorse.h
morse_decode_LDADD = libmorse.la

morse_encode_SOURCES = src/morse-encode.c include/libmorse.h
morse_encode_LDADD = libmorse.la

morse_uncompress_SOURCES = src/morse-uncompress.c include/libmorse.h
morse_uncompress_LDADD = libmorse.la
