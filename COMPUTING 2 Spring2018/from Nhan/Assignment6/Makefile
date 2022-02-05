CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  assignment6.o

assignment6: $(OBJECTS)
	$(CC) $(CFLAGS) -o assignment6 $(OBJECTS)
assignment6.o: assignment6.c
	$(CC) $(CFLAGS) -c assignment6.c -o assignment6.o
clean:
	rm assignment6 $(OBJECTS)
