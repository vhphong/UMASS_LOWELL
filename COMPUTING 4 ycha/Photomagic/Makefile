all: pixels clean

pixels: pixels.o LFSR.o
	g++ -g pixels.o LFSR.o --std=c++0x -lsfml-graphics -lsfml-window -lsfml-system -s -o pixels

pixels.o:
	g++ -g -c pixels.cpp

LFSR.o:
	g++ -g -c LFSR.cpp

clean:
	rm -rf *.o *.gch *~
