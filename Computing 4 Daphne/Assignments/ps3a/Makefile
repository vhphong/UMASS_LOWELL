CC = g++
CFLAGS = -Wall -ansi -pedantic -Werror -std=c++0x -lboost_unit_test_framework
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-system

all:NBody

NBody: nbody.o main.o
	$(CC) nbody.o main.o $(LFLAGS) -o NBody

main.o: main.cpp nbody.cpp
	$(CC) -c main.cpp $(CFLAGS)

nbody.o: nbody.cpp nbody.hpp
	$(CC) -c nbody.cpp $(CFLAGS)

clean:
	rm *.o NBody 
