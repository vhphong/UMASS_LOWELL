CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o ferry.o
ferry: $(OBJECTS)
	$(CC) $(CFLAGS) -o ferry $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm ferry $(OBJECTS)
