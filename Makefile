CC = g++
CFLAGS = -I.

DEPS = Wave.h Vector.h

LIBS=-lm -lncurses


%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(LIBS) 

test_wave: test_wave.o Wave.o Vector.o $(LIBS) 
	$(CC) -o test_wave test_wave.o Wave.o Vector.o  $(LIBS) 

clean:
	rm -f *.o test_wave
