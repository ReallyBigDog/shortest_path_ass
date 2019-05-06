CC = gcc
CFLAGS = -Wall -std=c99

all: system

system.o: system.c
	$(CC) $(CFLAGS) -c system.c

system: system.o
	$(CC) $(CFLAGS) -o system system.o

clean:
	rm *.o system
