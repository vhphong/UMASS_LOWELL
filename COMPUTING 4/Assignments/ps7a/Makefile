CC = g++
CFLAGS = -Wall -ansi -pedantic -Werror -ansi -std=c++0x -lboost_unit_test_framework 
LFLAGS = -lsfml-system -lsfml-audio -lsfml-graphics -lsfml-window -lboost_regex -lboost_date_time -lboost_unit_test_framework

.PHONY: all clean
all: ps7a

ps7a: main.o
	$(CC) main.o $(LFLAGS) -o ps7a
main.o: main.cpp
	$(CC) -c $< $(CFLAGS)

clean:
	rm ps7a main.o
