CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  assignment04.o

assignment04: $(OBJECTS)
	$(CC) $(CFLAGS) -o assignment04 $(OBJECTS)
assignment04.o: assignment04.c
	$(CC) $(CFLAGS) -c assignment04.c -o assignment04.o
clean:
	rm assignment04 $(OBJECTS)
