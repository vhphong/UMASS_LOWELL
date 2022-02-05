CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  main.o

hung: $(OBJECTS)
	$(CC) $(CFLAGS) -o hung $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm hung $(OBJECTS)
