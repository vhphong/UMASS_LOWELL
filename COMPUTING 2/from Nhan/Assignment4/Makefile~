CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  assignment03.o

assignment03: $(OBJECTS)
	$(CC) $(CFLAGS) -o assignment03 $(OBJECTS)
assignment03.o: assignment03.c
	$(CC) $(CFLAGS) -c assignment03.c -o assignment03.o
clean:
	rm assignment03 $(OBJECTS)
