/***********************************************************
Author: Nhan Tran
Date: 9/11/2017
Effort: 15 Minutes
Purpose: Getting know how to use left shift operator
***********************************************************/

#include <stdio.h>

int main(int argc, char *argv[] )
{
	unsigned int i = 1;
	int a = 0;
	while ( i != 0)
	{	
		printf("%d: %u\n", a, i);
		i = i << 1;
		a++;
	}
	return 0;
}