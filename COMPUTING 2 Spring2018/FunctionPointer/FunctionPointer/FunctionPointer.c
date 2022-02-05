// FunctionPointer.c : Defines the entry point for the console application.
//
#include <stdio.h>
#include <stdlib.h>
#include "stdafx.h"

void my_int_func(int x)
{
	printf("My number is: %d \n", x);
}

void displayNumber1(int y)
{
	printf("Hello world! and %d \n", y);
}

void displayNumber2()
{
	printf("Hello! \n");
}

int main()
{
	void (*fp_my_int_func)(int);
	fp_my_int_func = &my_int_func;

	void (*fp_displayNumber1)(int);
	fp_displayNumber1 = &displayNumber1;

	void (*fp_displayNumber2)();
	fp_displayNumber2 = &displayNumber2;

	// calls
	fp_my_int_func(2);
	fp_displayNumber1(8); // error: no print out
	fp_displayNumber2();
	printf("Hi FunctionPointer.c! \n");

	return 0;
}

