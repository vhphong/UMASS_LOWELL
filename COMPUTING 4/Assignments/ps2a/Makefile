CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -lboost_unit_test_framework
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-system -lboost_unit_test_framework

.PHONY: all clean

all: ps2a
ps2a: test.o LFSR.o
	$(CC) test.o LFSR.o -o ps2a $(LFLAGS)
test.o: test.cpp LFSR.hpp
	$(CC) -c $< $(CFLAGS)
LFSR.o: LFSR.cpp LFSR.hpp
	$(CC) -c $< $(CFLAGS)
clean:
	rm LFSR.o test.o ps2a