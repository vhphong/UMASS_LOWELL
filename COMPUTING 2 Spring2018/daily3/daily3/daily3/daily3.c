/***********************************************************
Author: Phong Vo
Date: 2/01/2018
Effort: 2hrs
Purpose: daily 3 assignment
***********************************************************/

#include "stdafx.h"
void set_flag(int* flag_holder, int flag_position);
int check_flag(int flag_holder, int flag_position);


int main()  
{
	int flag_holder = 0;
	int i;

	set_flag(&flag_holder, 3);
	set_flag(&flag_holder, 16);
	set_flag(&flag_holder, 31);

	for (i = 31; i >= 0; i--)
	{
		printf("%d", check_flag(flag_holder, i));
		if (i % 4 == 0)
		{
			printf(" ");
		}
	}
	printf("\n");
	return 0;
}

void set_flag(int *fh, int fp)
{
	int NUM_OF_BITS = 32;
	*fh = (*fh >> fp) | (*fh << (sizeof(*fh)*NUM_OF_BITS - fp));
	*fh = (*fh) | 1;
	*fh = (*fh << fp) | (*fh >> (sizeof(*fh)*NUM_OF_BITS - fp));
}
int check_flag(int fh, int fp)
{
	fh = fh >> fp;
	return fh & 1;
}