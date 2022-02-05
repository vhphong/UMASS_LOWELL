#include<stdio.h>
#include<stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[]){
	/* TA check point 1*/
	// MY_STRING hMyString = NULL;
	// hMyString = my_string_init_c_string("hi");
	// destroying hMyString
	// my_string_destroy(&hMyString);
	
	
	/* TA check point 2*/
	MY_STRING hMyString1, hMyString2;
	hMyString1 = my_string_init_c_string("abc xyz");
	hMyString2 = my_string_init_c_string("abcd xyz");
	
	printf("Size of hMyString1: %d \n", my_string_get_size(hMyString1));
	printf("Size of hMyString2: %d \n", my_string_get_size(hMyString2));
	
	printf("Comparison result: %d \n", my_string_compare(hMyString1, hMyString2));
	
	// destroying two strings
	my_string_destroy(&hMyString1);
	my_string_destroy(&hMyString2);
	
	return 0;
}
}