all: main clean

main: TextGenerator.o MarkovModel.o
	g++ -g TextGenerator.o MarkovModel.o --std=c++0x -o main

TextGenerator.o: TextGenerator.cpp
	g++ -g -c TextGenerator.cpp --std=c++0x

mmtest: mmtest.o MarkovModel.o
	g++ -g mmtest.o MarkovModel.o -o test -lboost_unit_test_framework

mmtest.o: mmtest.cpp
	g++ -g -c mmtest.cpp -lboost_unit_test_framework

MarkovModel.o: MarkovModel.cpp MarkovModel.hpp
	g++ -g -c MarkovModel.cpp --std=c++0x

clean: 
	rm -rf *.o *.gch *~

