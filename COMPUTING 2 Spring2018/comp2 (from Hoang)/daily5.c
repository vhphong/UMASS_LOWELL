/******************************************************************************
Author: Hoang Do
Date: 9/25/2017
Effort: 1 hour
Purpose: Learn how to work with bitwise operation and using in the array
******************************************************************************/

#include <stdio.h>

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);

int main(int argc, char* argv[]) 
{
	unsigned int flag_holder[5] = { 0 };
	//Set the first integer to zero and all others to zero by default.

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

void set_flag(unsigned int flag_holder[], int flag_position) {
	int array, bit, temp;

	if (flag_position < 32) 
	{
		array = 0;
		bit = flag_position;
	}
	else 
	{
		array = flag_position / 32;
		bit = flag_position % 32;
	}

	temp = 1 << (bit - 1);

	if ((flag_holder[array] & temp) != temp) 
	{
		flag_holder[array] = flag_holder[array] + temp;
	}
}

void unset_flag(unsigned int flag_holder[], int flag_position) {
	int array, bit, temp;

	if (flag_position < 32) 
	{
		array = 0;
		bit = flag_position;
	}
	else 
	{
		array = flag_position / 32;
		bit = flag_position % 32;
	}

	temp = 1 << (bit - 1);

	if ((flag_holder[array] & temp) == temp) 
	{
		flag_holder[array] = flag_holder[array] - temp;
	}
}

int check_flag(unsigned int flag_holder[], int flag_position) {
	int array, bit, temp;

	if (flag_position < 32) 
	{
		array = 0;
		bit = flag_position;
	}
	else 
	{
		array = flag_position / 32;
		bit = flag_position % 32;
	}

	temp = flag_holder[array] >> (bit - 1);

	return (temp & 1);
}



void display_flags(unsigned int flag_holder[], int size) {
	int i;

	for (i = 0; i < size; i++) 
	{
		display_32_flags_as_array(flag_holder[i]);
		printf("\n");
	}
}


void display_32_flags_as_array(unsigned int flag_holder) {
	int tempArray[1] = { flag_holder };
	int i;
	int x = 1;

	for (i = 0; i < 32; i++) 
	{
		printf("%d", check_flag(tempArray, i));

		if (x % 4 == 0) 
		{
			printf(" ");
			
		}
		x++;
	}	
}
