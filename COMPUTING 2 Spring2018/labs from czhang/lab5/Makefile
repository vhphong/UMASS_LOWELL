CC = gcc
CFLAGS = -Wall --std=c99 -g
OBJECTS = main.o my_string.o
TEST_OBJECTS = unit_test.o test_def.o

string_driver: $(OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(OBJECTS)

unit_test: my_string.o unit_test.o test_def.o 
	$(CC) $(CFLAGS) -o unit_test unit_test.o test_def.o my_string.o	
	
main.o: main.c 
	$(CC) $(CFLAGS) -c main.c

my_string.o: my_string.c my_string.h
	$(CC) $(CFLAGS) -c my_string.c my_string.h

unit_test.o: unit_test.c
	$(CC) $(CFLAGS) -c unit_test.c

test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c

clean:
	rm string_driver unit_test $(TEST_OBJECTS) $(OBJECTS)
