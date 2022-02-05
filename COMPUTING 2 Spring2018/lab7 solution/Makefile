CC = gcc
CFLAGS = -Wall --std=c99
HANGMAN_OBJECTS = main.o my_string.o generic_vector.o
TEST_OBJECTS = unit_test.o test_def.o my_string.o

string_driver: $(HANGMAN_OBJECTS)
	$(CC) $(CFLAGS) -o string_driver $(HANGMAN_OBJECTS)

unit_test: $(TEST_OBJECTS)
	$(CC) $(CFLAGS) -o unit_test $(TEST_OBJECTS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c -o main.o

my_string.o: my_string.c my_string.h generic.h
	$(CC) $(CFLAGS) -l my_string.h -l generic.h -c my_string.c -o my_string.o

generic_vector.o: generic_vector.c generic_vector.h generic.h
	$(CC) $(CFLAGS) -l generic_vector.h -l generic.h -c generic_vector.c -o generic_vector.o

unit_test.o: unit_test.c unit_test.h
	$(CC) $(CFLAGS) -l unit_test.h -c unit_test.c -o unit_test.o

test_def.o: test_def.c
	$(CC) $(CFLAGS) -c test_def.c -o test_def.o

clean:
	rm string_driver unit_test unit_test.o test_def.o $(HANGMAN_OBJECTS)
