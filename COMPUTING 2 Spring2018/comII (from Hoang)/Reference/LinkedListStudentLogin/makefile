CC = gcc
CFLAGS = -Wall -W
DBGFLAG = -g -DEBUG
all: main.o linkedListSt.o
	$(CC) main.o linkedListSt.o -o main
main.o: main.c linkedListSt.h
	$(CC) -c main.c
linkedListSt.o: linkedListSt.c
	$(CC) -c linkedListSt.c
debug: main.o linkedListSt.o
	$(CC) $(DBGFLAG) main.o linkedListSt.o -o main
clean: 
	rm *.o 

	