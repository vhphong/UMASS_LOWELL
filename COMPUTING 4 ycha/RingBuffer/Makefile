all: main clean

main: main.o RingBuffer.o
	g++ -g main.o RingBuffer.o -o main --std=c++0x

main.o: main.cpp
	g++ -g -c main.cpp

RingBuffer.o: RingBuffer.cpp RingBuffer.hpp
	g++ -g -c RingBuffer.cpp -lfsml-system --std=c++0x

clean: 
	rm -rf *.o *.gch *~ 
