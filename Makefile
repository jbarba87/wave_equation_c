CC = g++
CFLAGS = -I.

DEPS = Wave.h Vector.h

LIBS=-lm


%.o: %.c $(DEPS)
	$(CC) -c -o $@ $<

test_wave: test_wave.o Wave.o Vector.o
	$(CC) -o test_wave test_wave.o Wave.o Vector.o

clean:
	rm -f *.o test_wave
