CC = gcc
CFLAGS = -Wall -W
DBGFLAG = -g -DEBUG
all : main.o linked_queue.o
	$(CC) -g -o main main.o linked_queue.o 
main.o : main.c linked_queue.h
	$(CC) -c -g  main.c
linked_queue.o : linked_queue.c
	$(CC) -c -g linked_queue.c
debug : main.o linked_queue.o
	$(CC) $(DBGFLAG) -o main main.o linked_queue.o
clean :
	rm *.o main
