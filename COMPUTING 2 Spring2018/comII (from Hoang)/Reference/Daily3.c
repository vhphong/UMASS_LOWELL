/***********************************************************
Author: <Rushabh Doshi>
Date: <9/17/2016>
Effort: <3 hours>
Purpose: <Understand and edit the functions and the 4 
		  different operators>
***********************************************************/



#include <stdio.h>
void set_flag(int* flag_holder, int flag_position);
int check_flag(int flag_holder, int flag_position);


int main(int argc, char* argv[])
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

void set_flag(int *flag_holder, int flag_position)
{


	*flag_holder = *flag_holder | (1 << flag_position);
}


int check_flag(int flag_holder, int flag_position)
{
	
	return (flag_holder >>= flag_position) & 1;
	
}