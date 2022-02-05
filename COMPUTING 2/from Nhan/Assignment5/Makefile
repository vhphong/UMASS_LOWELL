CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  assignment05.o

assignment05: $(OBJECTS)
	$(CC) $(CFLAGS) -o assignment05 $(OBJECTS)
assignment05.o: assignment05.c
	$(CC) $(CFLAGS) -c assignment05.c -o assignment05.o
clean:
	rm assignment05 $(OBJECTS)
