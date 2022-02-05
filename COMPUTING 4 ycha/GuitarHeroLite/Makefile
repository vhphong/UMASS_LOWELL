all: main

main: main.o GuitarString.o RingBuffer.o
	g++ -g main.o GuitarString.o RingBuffer.o -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio --std=c++0x -o main

main.o: main.cpp
	g++ -g -c main.cpp -lsfml-system -lsfml-window -lsfml-graphics -lsfml-audio --std=c++0x

test: test.o RingBuffer.o
	g++ -g test.o RingBuffer.o -o test -lboost_unit_test_framework

test.o: test.cpp
	g++ -g -c test.cpp -lboost_unit_test_framework

testGS: testGS.o GuitarString.o RingBuffer.o
	g++ -g testGS.o GuitarString.o RingBuffer.o -o testGS -lboost_unit_test_framework

testGS.o: testGS.cpp
	g++ -g -c testGS.cpp -lboot_unit_test_framework

GuitarString.o: GuitarString.cpp GuitarString.hpp
	g++ -g -c GuitarString.cpp 

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	g++ -g -c RingBuffer.cpp --std=c++0x

clean: 
	rm -rf *.o *.gch *~ 

