/***********************************************************
Author: Nhan Tran
Date: 9/25/2017
Effort: 6 hours
Purpose: Understand C bitwise operator
***********************************************************/

#include <stdio.h>

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);
int check_32_flags(unsigned int flag_holder, int flag_position);

int main(int argc, char* argv[])
{
	unsigned int flag_holder[5] = {0};
	
	
	set_flag(flag_holder, 3);
	set_flag(flag_holder, 16);
	set_flag(flag_holder, 31);
	set_flag(flag_holder, 87);
	
	display_flags(flag_holder, 5);
	printf("\n\n");
	
	unset_flag(flag_holder, 31);
	unset_flag(flag_holder, 3);
	set_flag(flag_holder, 99);
	set_flag(flag_holder, 100);
	
	display_flags(flag_holder, 5);
	return 0;

}

void set_flag(unsigned int flag_holder[], int flag_position)
{
	int i, p, j = 1;
	i = flag_position / 32;
	p = flag_position % 32;
	j = j << p;
	flag_holder[i] = flag_holder[i] | j;
}

int check_flag(unsigned int flag_holder[], int flag_position)
{
	int i, p, j = 1;	
	i = flag_position / 32;
	p = flag_position % 32;
	j = j << p;
	if( (j & flag_holder[i]) != 0)
		return 1;
	else 
		return 0;
}

int check_32_flags(unsigned int flag_holder, int flag_position) 
{
	int index;
	index = 1 << flag_position;
	if (flag_holder & index) 
		return 1;
	return 0;
}

void display_32_flags(unsigned int flag_holder)
{
	int i;
	for(i = 0; i < 32  ; i++)
	{
		printf("%d", check_32_flags(flag_holder,i));
		if(i % 4 == 3)
		{
			printf(" ");
		}
	}
	printf("\n");
}

void unset_flag(unsigned int flag_holder[], int flag_position)
{
	int i, p, j;
	i = flag_position / 32;
	p = flag_position % 32;
	j = 1 << p;
	flag_holder[i] = flag_holder[i] ^ j;
}

void display_flags(unsigned int flag_holder[], int size)
{
	int i;
	for (i = 0; i < size; i++)
	{
		display_32_flags(flag_holder[i]);
		printf("\n");
	}
}