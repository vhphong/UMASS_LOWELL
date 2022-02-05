CC = g++
CFLAGS = -Wall -Werror -ansi -pedantic 
LFLAGS = -lsfml-window -lsfml-graphics -lsfml-audio -lsfml-system

all:  sierpinski original

sierpinski: main.o sierpinski.o
	$(CC) main.o sierpinski.o -o sierpinski $(LFLAGS) 

main.o: main.cpp sierpinski.hpp
	$(CC) -c main.cpp $(CFLAGS)

sierpinski.o: sierpinski.cpp sierpinski.hpp
	$(CC) -c sierpinski.cpp $(CFLAGS) 

original: maino.o original.o
	$(CC) maino.o original.o -o original $(LFLAGS) 

maino.o: maino.cpp original.hpp
	$(CC) -c maino.cpp $(CFLAGS)  

original.o: original.cpp original.hpp
	$(CC) -c original.cpp $(CFLAGS)  

clean:
	rm *.o sierpinski original
