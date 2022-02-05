all: main clean

main: main.o
	g++ -g main.o --std=c++0x -o main -lboost_regex -lboost_date_time

main.o: main.cpp
	g++ -g -c main.cpp --std=c++0x 

clean: 
	rm -rf *.o *.gch *~

