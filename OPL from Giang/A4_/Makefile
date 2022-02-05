test: test1 test2 test3 A4-tests

test1: test1.cpp tombstones.h
	g++ -o test1.o test1.cpp
test2: test2.cpp tombstones.h
	g++ -o test2.o test2.cpp
test3: test3.cpp tombstones.h
	g++ -o test3.o test3.cpp
A4-tests: A4-tests.cpp tombstones.h
	g++ -o A4-tests.o A4-tests.cpp

clean:
	rm -f *.o