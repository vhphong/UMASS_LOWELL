CC = gcc
CFLAGS = -Wall -W
DBGFLAG = -g -DEBUG
all : main.o stack.o
	$(CC)  main.o stack.o -o main
main.o : main.c stack.h
	$(CC) -c  main.c
stack.o : stack.c
	$(CC) -c  stack.c
debug : main.o stack.o
	$(CC) $(DBGFLAG) main.o stack.o -o main
clean :
	rm *.o main
