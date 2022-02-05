CC = g++
CFLAGS = -Wall -Werror -pedantic -ansi -std=c++0x -lboost_unit_test_framework
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-system -lboost_unit_test_framework

.PHONY: all clean

all: ps5a

ps5a: RingBuffer.o test.o
	$(CC) RingBuffer.o test.o -o ps5a $(LFLAGS)
RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	$(CC) -c $< $(CFLAGS)
test.o: test.cpp RingBuffer.hpp
	$(CC) -c $< $(CFLAGS)
clean:
	rm RingBuffer.o test.o ps5a
