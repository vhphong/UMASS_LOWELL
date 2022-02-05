CC = g++
CFLAGS = -g -Wall -ansi -pedantic -Werror -std=c++0x -lboost_unit_test_framework
LFLAGS = -g -lsfml-window -lsfml-graphics -lsfml-system -std=c++0x -lboost_unit_test_framework

.PHONY: all clean

all: ED

ED: main.o EditDistance.o
	$(CC) main.o EditDistance.o -o ED $(LFLAGS)

main.o: main.cpp EditDistance.hpp
	$(CC) -c $< $(CFLAGS)

EditDistance.o: EditDistance.cpp EditDistance.hpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm EditDistance.o main.o ED
