all: main.h main.o
	gcc -Wall -o main main.o

main.o: main.h main.c
	gcc -c main.c

run:
	./main bestfit 1024 proj5_data.txt > best1024Results.txt
	./main firstfit 1024 proj5_data.txt > first1024Results.txt
	./main buddysys 1024 proj5_data.txt > buddy1024Results.txt
	./main buddysys 512 proj5_data.txt > buddy512Results.txt
	./main firstfit 512 proj5_data.txt > first512Results.txt
	./main bestfit 512 proj5_data.txt > buddy512Results.txt

clean:
	rm -rf *.o main *Results.txt