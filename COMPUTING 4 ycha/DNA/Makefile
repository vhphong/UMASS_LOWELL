all: main clean

main:  main.o EditDistance.o
	g++ -g main.o EditDistance.o --std=c++0x -lsfml-system -o1 -g -o main 

main.o:
	g++ -g -c main.cpp

EditDistance.o:
	g++ -g -c EditDistance.cpp 

clean:
	rm -rf *.o *.gch *~

