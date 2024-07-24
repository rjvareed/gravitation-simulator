CC = gcc
CFLAGS = -Wall `pkg-config --cflags gtk+-3.0`
LDFLAGS = `pkg-config --libs gtk+-3.0` -lm -lpthread

all: main.c
	$(CC) -c drawing.c $(CFLAGS) 
	$(CC) -c main.c $(CFLAGS)
	$(CC) main.o drawing.o -o app $(CFLAGS) $(LDFLAGS)

clean:
	rm -f *.o
