/***********************************************************
Author: Phong Vo
Date: 1/28/2018
Effort: 2hrs
Purpose: daily 2 assignment
***********************************************************/

#include "stdafx.h"
#include <stdio.h>
//#include <stdlib.h>
//#include <math.h>

int main(int argc, char* agrv[])
{
	unsigned int x = 1;
	int i;
	for (i = 0; x != 0; i++)
	{
		printf("%d: %d\n", i, x);
		x = x << 1;
	}

	return 0;
}