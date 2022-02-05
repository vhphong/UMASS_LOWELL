/******************************************************************************
Author: Rushabh Doshi
Date: September 25, 2016
Effort: 99 minutes
Purpose: This assignment allows us to further practice with
bitwise operators and get the idea of creating aset of
functions for interacting with an object type.
******************************************************************************/

#include <stdio.h>

void set_flag(unsigned int flag_holder[], int flag_position);
void unset_flag(unsigned int flag_holder[], int flag_position);
int check_flag(unsigned int flag_holder[], int flag_position);
void display_32_flags_as_array(unsigned int flag_holder);
void display_flags(unsigned int flag_holder[], int size);

int main(int argc, char* argv[]) {
	//first integer is set to zero and all others to zero normally
	unsigned int flag_holder[5] = { 0 };

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
	int arrayIndex, bitPosition, checker;
	int maxBits = 32;

	if (flag_position < maxBits) {
		arrayIndex = 0;
		bitPosition = flag_position;
	}
	else {
		arrayIndex = flag_position / maxBits;
		bitPosition = flag_position % maxBits;
	}

	checker = 1 << (bitPosition - 1);

	if ((flag_holder[arrayIndex] & checker) != checker) {
		flag_holder[arrayIndex] = flag_holder[arrayIndex] + checker;
	}
}

void unset_flag(unsigned int flag_holder[], int flag_position) {
	int arrayIndex, bitPosition, checker;
	int maxBits = 32;

	if (flag_position < maxBits) {
		arrayIndex = 0;
		bitPosition = flag_position;
	}
	else {
		arrayIndex = flag_position / maxBits;
		bitPosition = flag_position % maxBits;
	}

	checker = 1 << (bitPosition - 1);

	if ((flag_holder[arrayIndex] & checker) == checker) {
		flag_holder[arrayIndex] = flag_holder[arrayIndex] - checker;
	}
}

int check_flag(unsigned int flag_holder[], int flag_position) {
	int arrayIndex, bitPosition, checker;
	int maxBits = 32;

	if (flag_position < maxBits) {
		arrayIndex = 0;
		bitPosition = flag_position;
	}
	else {
		arrayIndex = flag_position / maxBits;
		bitPosition = flag_position % maxBits;
	}

	checker = flag_holder[arrayIndex] >> (bitPosition - 1);

	return (checker & 1);
}



void display_flags(unsigned int flag_holder[], int size) {
	int i;

	for (i = 0; i < size; i++) {
		display_32_flags_as_array(flag_holder[i]);
		printf("\n");
	}
}


void display_32_flags_as_array(unsigned int flag_holder) {
	int tempArray[1] = { flag_holder };
	int maxBits = 32;
	int i;
	int x = 1;

	for (i = 0; i < maxBits; i++) {
		printf("%d", check_flag(tempArray, i));

		if (x % 4 == 0) {
			printf(" ");
			
		}
		x++;
	}	
}