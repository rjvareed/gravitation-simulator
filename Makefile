CC = gcc
CFLAGS = -O3 -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lm -lpthread

all: main.c
	$(CC) -c drawing.c $(CFLAGS) 
	$(CC) -c main.c $(CFLAGS)
	$(CC) -c calc.c $(CFLAGS)
	$(CC) main.o drawing.o calc.o -o app $(CFLAGS) $(LDFLAGS)
	rm -f *.o

clean:
	rm -f *.o
	rm app
