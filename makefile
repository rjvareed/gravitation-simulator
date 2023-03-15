CC = gcc
CFLAGS = -Wall -g `pkg-config --cflags gtk+-3.0` -lm -lpthread
LDFLAGS = `pkg-config --libs gtk+-3.0`

all: main.c
	#TODO figure out whether to include the flags or if it is redundant
	$(CC) -c drawing.c $(CFLAGS) 
	$(CC) -c main.c $(CFLAGS)
	$(CC) main.o drawing.o -o app $(CFLAGS) $(LDFLAGS)
	rm -f *.o

clean:
	rm -f *.o
