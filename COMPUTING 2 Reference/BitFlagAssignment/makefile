CC = gcc
CFLAGS = -Wall -W
DBGFLAG = -g -DEBUG
all : main.o bit_flags.o
	$(CC) -g  -o main main.o bit_flags.o 
main.o : main.c bit_flags.h
	$(CC) -c  -g main.c
bit_flags.o : bit_flags.c
	$(CC) -c -g bit_flags.c
clean :
	rm *.o main
