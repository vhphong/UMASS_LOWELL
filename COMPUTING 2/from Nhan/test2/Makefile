CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  program1.o

stack: $(OBJECTS)
	$(CC) $(CFLAGS) -o stack $(OBJECTS)
program1.o: program1.c
	$(CC) $(CFLAGS) -c program1.c -o program1.o
clean:
	rm stack $(OBJECTS)
