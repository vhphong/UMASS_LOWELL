CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic -std=c++0x -lboost_unit_test_framework
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system -lboost_unit_test_framework

.PHONY: all clean

all: GuitarHero gstest

GuitarHero: GuitarString.o GuitarHero.o RingBuffer.o
	$(CC) GuitarString.o GuitarHero.o RingBuffer.o $(LFLAGS) -o GuitarHero

gstest: GuitarString.o GStest.o RingBuffer.o
	$(CC) GuitarString.o GStest.o RingBuffer.o $(LFLAGS) -o gstest

GuitarHero.o: GuitarHero.cpp GuitarString.hpp RingBuffer.hpp
	$(CC) -c $< $(CFLAGS)

GuitarString.o: GuitarString.cpp GuitarString.hpp RingBuffer.hpp
	$(CC) -c $< $(CFLAGS)

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm *.o  GuitarHero gstest
