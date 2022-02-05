CC=g++
CFLAGS=-g -std=c++11 -pedantic -Wall -Werror
O_FILES=Scanner.o Parser.o 
BOOSTFLAG= -lboost_unit_test_framework 
all: main test
main: main.cpp Scanner.o Parser.o 
	$(CC) $(CFLAGS) -o main main.cpp $(O_FILES)
test: main
	./main < test.txt
test_scanner: test_driver.o Scanner.o Parser.o
	$(CC) $(CFLAGS) -o test test_driver.o Scanner.o Parser.o $(BOOSTFLAG)
	make test_alpha
	make test_digit
	make test_operator
test_driver.o : test.cpp
	$(CC) $(CFLAGS) -o test_driver.o  -c test.cpp
Scanner.o: Scanner.cpp Scanner.h
	$(CC) $(CFLAGS) -o Scanner.o -c Scanner.cpp
Parser.o: Parser.cpp Parser.h
	$(CC) $(CFLAGS) -o Parser.o -c Parser.cpp
test_alpha : test
	./test --log_level=success < alpha.txt --run_test=T_ALPHA
test_digit : test
	./test --log_level=success < digit.txt --run_test=T_DIGIT
test_operator : test
	./test --log_level=success < operator.txt --run_test=T_OPERATOR
clean: 
	rm -rf *.o main main.dSYM test
