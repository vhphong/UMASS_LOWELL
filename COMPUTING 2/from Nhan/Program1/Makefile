CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o bit_flags.o
bit_flags: $(OBJECTS)
	$(CC) $(CFLAGS) -o bit_flags $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm bit_flags $(OBJECTS)
