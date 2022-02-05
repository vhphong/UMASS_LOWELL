all: ps4.o
	gcc -std=c++0x ps4.o -o pc_threads
ps4.o: ps4.h ps4.c
	gcc -c ps4.c
clean:
	rm -rf pc_threads ps4.o