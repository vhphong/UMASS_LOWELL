all: main.o
	gcc  -D_FILE_OFFSET_BITS=64 -g -o main main.o

main.o : main.c main.h
	gcc -c main.c

clean:
	rm *.o main