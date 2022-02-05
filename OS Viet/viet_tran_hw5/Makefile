# Assignment 5: Makefile
# Name: Viet Tran
# E-mail: viet_tran1@student.uml.edu

p5: main.o bestFit.o firstFit.o buddySys.o utility2.o
	gcc -o p5 main.o bestfit.o firstfit.o buddysys.o utility2.o -lm

main.o: main.c main.h
	gcc -c main.c

bestFit.o: bestfit.c main.h
	gcc -c bestfit.c

firstFit.o: firstfit.c main.h
	gcc -c firstfit.c

buddySys.o: buddysys.c main.h
	gcc -c buddysys.c
utility2.o: utility2.c utility.h
	gcc -c utility2.c 

clean:
	rm *.o
	rm p5
