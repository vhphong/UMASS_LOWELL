CC = g++
CFLAGS = -Wall -ansi -pedantic -Werror -std=c++0x -lboost_unit_test_framework
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-system -lboost_unit_test_framework

.PHONY: all clean

all: PhotoMagic

PhotoMagic: PhotoMagic.o LFSR.o
	$(CC) PhotoMagic.o LFSR.o -o PhotoMagic $(LFLAGS) 

PhotoMagic.o: PhotoMagic.cpp LFSR.hpp
	$(CC)  -c $< $(CFLAGS)

LFSR.o: LFSR.cpp LFSR.hpp
	$(CC)  -c $< $(CFLAGS)

clean:
	rm *.o PhotoMagic

	
	


