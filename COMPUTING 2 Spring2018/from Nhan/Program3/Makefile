CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  program3.o

sort: $(OBJECTS)
	$(CC) $(CFLAGS) -o sort $(OBJECTS)
program3.o: program3.c
	$(CC) $(CFLAGS) -c program3.c -o program3.o
clean:
	rm sort $(OBJECTS)