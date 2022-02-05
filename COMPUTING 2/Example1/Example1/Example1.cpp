// Example1.cpp : Defines the entry point for the console application.
//

#include "stdio.h"
#include "stdlib.h"
void output_date(int month, int day, int year);

int main(int argc, char* agrv[])
{
	int month;
	int day;
	int year;
	month = 1;
	day = 26;
	year = 2018;
	output_date(month, day, year);

    return 0;
}

void output_date(int month, int day, int year)
{
	printf("%d/%d/%d\n", month, day, year);
}