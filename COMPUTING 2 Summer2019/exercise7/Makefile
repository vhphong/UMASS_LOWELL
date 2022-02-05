CC = gcc
CFLAGS = -g -Wall --std=c99
OBJECTS =  main.o priority_queue.o

priority_q: $(OBJECTS)
	$(CC) $(CFLAGS) -o priority_queue $(OBJECTS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o
clean:
	rm priority_queue $(OBJECTS)
