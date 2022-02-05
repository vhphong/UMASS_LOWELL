CC     = gcc
CFLAGS = -Wall -Werror -c -o
OBJS   = main.o my_vector.o my_string.o Evil_Hangman.o associative_array.o


hangman : $(OBJS) 
	$(CC) -o hangman $(OBJS)

main.o : my_vector.h Evil_Hangman.h main.c my_vector.c Evil_Hangman.c
	$(CC) $(CFLAGS) main.o main.c

my_vector.o : my_vector.h common.h my_vector.c 
	$(CC) $(CFLAGS) my_vector.o my_vector.c

associative_array.o : my_string.h my_vector.h associative_array.h common.h my_string.c my_vector.c associative_array.c
	$(CC) $(CFLAGS) associative_array.o associative_array.c

Evil_Hangman.o : my_string.h my_vector.h associative_array.h common.h Evil_Hangman.h my_string.c my_vector.c associative_array.c Evil_Hangman.c
	$(CC) $(CFLAGS) Evil_Hangman.o Evil_Hangman.c

my_string.o : my_string.h my_string.c
	$(CC) $(CFLAGS) my_string.o my_string.c
	
	
unit_test: my_string.o unit_test.o test_def.o
	$(CC) -o unit_test unit_test.o my_string.o test_def.o
	
unit_test.o: unit_test.c my_string.h unit_test.h
	$(CC) $(CFLAGS) unit_test.o unit_test.c 
	
test_def.o: test_def.c unit_test.h my_string.h
	$(CC) $(CFLAGS) test_def.o test_def.c
	
	
clean :
	$(RM) *.o *~ $(MAIN)