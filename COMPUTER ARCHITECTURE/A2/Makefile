CC = g++

CFLAGS =  -Wall -ansi -pedantic -Werror

main:  main.o
	$(CC) main.o $(CFLAGS) -o main

main.o:  main.c
	$(CC) -c $(CFLAGS) main.c

clean:
	rm main main.o
