CC=gcc
CFLAGS=-g -Wextra -Wall

all: tail

run: all
	./tail

tail.o: tail.c
	$(CC) $(CFLAGS) -c tail.c -o tail.o

tail: tail.o
	$(CC) $(CFLAGS) tail.o -o tail
