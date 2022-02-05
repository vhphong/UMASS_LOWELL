CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o my_string.o

lab3: $(OBJECTS)
	$(CC) $(CFLAGS) -o lab3 $(OBJECTS)
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c
my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c my_string.h
clean:
	rm lab3 $(OBJECTS)
