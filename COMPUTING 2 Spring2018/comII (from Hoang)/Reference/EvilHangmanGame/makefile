CC = gcc 
CFLAGS = -Wall
DBGFLAG = -DEBUG 
OBJECTS = hangman.o string.o vector_string.o binary_search_tree.o
HEADER = string.h vector_string.h binary_search_tree.h
all : $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o hangman
hangman.o : hangman.c $(HEADER)
	$(CC) -c hangman.c
string.o : string.c
	$(CC) -c string.c
vector_string.o : vector_string.c
	$(CC) -c vector_string.c
binary_search_tree.o : binary_search_tree.c
	$(CC) -c binary_search_tree.c
debug : $(OBJECTS)
	$(CC) $(DBGFLAG) $(OBJECTS) -o hangman
clean :
	rm *.o hangman
