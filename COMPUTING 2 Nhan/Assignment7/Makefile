CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  main.o stack.o

stack: $(OBJECTS)
	$(CC) $(CFLAGS) -o stack $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm stack $(OBJECTS)
