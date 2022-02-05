// FunctionPointer.cpp : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

void my_int_func(int x)
{
	printf("My number is: %d \n", x);
}

void display()
{
	printf("Hello world! \n");
}

int main()
{
	void (*foo)(int);
	foo = &my_int_func;

	void (*func_1);
	func_1 = &display;

	foo(2);
	func_1;
	//printf("Hi there! \n");

	return 0;
}

