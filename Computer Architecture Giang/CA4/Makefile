hw4symasm_all: hw4symasm.o lex.yy.o
	gcc -o hw4symasm_all hw4symasm.o lex.yy.o
hw4symasm.o:  hw4symasm.c
	gcc -c -g hw4symasm.c
lex.yy.o:  lex.yy.c
	gcc -c -g lex.yy.c
lex.yy.c: hw4symasm.ll
	flex hw4symasm.ll
clean:
	rm lex.yy.o lex.yy.c hw4symasm.o hw4symasm_all