CC = g++
CFLAGS = -Wall -ansi -pedantic -Werror -std=c++0x 
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lboost_unit_test_framework

.PHONY: all clean

all: TextGenerator mmtest

TextGenerator: MarkovModel.o TextGenerator.o
	$(CC) MarkovModel.o TextGenerator.o $(LFLAGS) -o TextGenerator

mmtest: MarkovModel.o mmtest.o
	$(CC) MarkovModel.o mmtest.o $(LFLAGS) -o mmtest

MarkovModel.o: MarkovModel.cpp MarkovModel.hpp
	$(CC) -c $< $(CFLAGS)

TextGenerator.o: TextGenerator.cpp
	$(CC) -c $< $(CFLAGS)

mmtest.o: mmtest.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o TextGenerator  mmtest
