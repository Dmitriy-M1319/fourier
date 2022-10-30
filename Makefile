CC = gcc
CFLAGS = -g -Wall -Wextra -pedantic

.PHONY: all clean

all: create_signals create_spectrums

clean:
	rm *.o create_signals create_spectrums

create_signals: create_signals.c signals.o
	$(CC) $(CFLAGS) signals.o create_signals.c -lm -o create_signals

create_spectrums: create_spectrums.c spectrums.o signals.o synth.o
	$(CC) $(CFLAGS) signals.o spectrums.o synth.o create_spectrums.c -lm -lfftw3 -o create_spectrums

signals.o: signals.c
	$(CC) $(CFLAGS) -c signals.c -lm

spectrums.o: spectrums.c
	$(CC) $(CFLAGS) -c spectrums.c -lm

synth.o: synth.c
	$(CC) $(CFLAGS) -c synth.c -lm -lfftw3
