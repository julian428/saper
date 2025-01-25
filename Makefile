CC = gcc
CFLAGS = -Wall

all: saper

saper: main.o board.o config.o
	$(CC) $(CFLAGS) -o saper main.o board.o config.o

main.o: main.c board.h config.h
	$(CC) $(CFLAGS) -c main.c

board.o: board.c board.h
	$(CC) $(CFLAGS) -c board.c

config.o: config.c config.h
	$(CC) $(CFLAGS) -c config.c

clean:
	rm saper test *.o *.txt

test: all
	$(CC) -o test test.c config.c board.c -I. $(CFLAGS)
	./test