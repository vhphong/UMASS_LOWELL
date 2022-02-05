parse: parse.o scan.o
	g++ -o parse parse.o scan.o

parse.o: scan.h

scan.o: scan.h

clean:
	rm *.o parse

test: parse
	./parse < ./primes.cl
