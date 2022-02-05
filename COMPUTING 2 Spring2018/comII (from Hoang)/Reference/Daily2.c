/***********************************************
Author: <Rushabh Doshi>
Date: <9-11-2016>
Effort: <10 minutes~>
Purpose: <To understand the "<<" operator as it 
		  shifts the value of the bit over by 1>

***********************************************/


#include <stdio.h>
int main(int argc, char* argv[])
{
	unsigned x = 1;
	for (int i = 0; x != 0; i++)
	{
		printf("%d:%u\n", i, x);
		x = x << 1;
			
	}


	return 0;
}