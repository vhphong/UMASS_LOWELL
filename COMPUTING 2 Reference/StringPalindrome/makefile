CC = gcc
CFLAGS = -Wall -W
DBGFLAG = -g -DEBUG
all : main.o palindrome.o
	$(CC) -g main.o palindrome.o -o main
main.o : main.c palindrome.h
	$(CC) -c -g main.c
palindrome.o : palindrome.c
	$(CC) -c -g palindrome.c
debug : main.o palindrome.o
	$(CC)	$(DBGFLAG) main.o palindrome.o -o main
clean :
	rm *.o main
