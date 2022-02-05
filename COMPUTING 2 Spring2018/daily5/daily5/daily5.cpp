/***********************************************************
Author: Phong Vo
Date: 2/08/2018
Effort: 2hrs
Purpose: daily 5 assignment
***********************************************************/
#include <stdio.h>
#include <stdlib.h>

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);
int main(int argc, char* argv[])
{
	unsigned int flag_holder[5] = { 0 };//Set the first integer to zero and all others to zero by default.
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

void display_flags(unsigned int flag_holder[], int size)
{
	int i;
	for (i = 0; i < size; i++)
		display_32_flags_as_array(flag_holder[i]);
}
void display_32_flags_as_array(unsigned int flag_holder)
{
	int i;
	for (i = 0; i < 32; i++)
	{
		if (i % 4 == 0)
		{
			printf(" ");
		}

		printf("%d", check_flag(&flag_holder, i)); //since check flag expects array/address, we will pass address
	}
	printf("\n");
}

void set_flag(unsigned int flag_holder[], int flag_position)
{
	int index = flag_position / 32; //find out which number in the array should be modified
	int bit_position = flag_position % 32; // find out which bit in the selected number will be modified
	int value = 1 << bit_position; //move 1 to specified bit position
	flag_holder[index] = flag_holder[index] | value; //set the bit in the selected number at index
}
int check_flag(unsigned int flag_holder[], int flag_position)
{
	int index = flag_position / 32; //find out which number in the array is requested
	int bit_position = flag_position % 32; // find out which bit in the selected number
	int value = 1 << bit_position; //move 1 to the specified position
	int bit = flag_holder[index] & value; //extract the bit

	if (bit == 0)
		return 0;
	else
		return 1;
}

void unset_flag(unsigned int flag_holder[], int flag_position)
{
	int index = flag_position / 32; //find out which number in the array is requested
	int bit_position = flag_position % 32; // find out which bit in the selected number
	int value = 1 << bit_position; //move 1 to the specified position

	value = ~value; //invert the bits, so all except the flag position are 1. the bit in flag postion is 0
	flag_holder[index] = flag_holder[index] & value;//& the value so the bitposition is cleared
}