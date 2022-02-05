#include <stdio.h> 
#include <stdlib.h> 
#include "my_string.h"

int main(int argc, char* argv[]) 
{
	MY_STRING hMy_string1, hMy_string2 = NULL;

	//hMy_string = my_string_init_default();
	hMy_string1 = my_string_init_c_string("hi");
	hMy_string2 = my_string_init_c_string("hihi");

	printf("hMy_string1 size: %d\n", my_string_get_size(hMy_string1));
	printf("hMy_string2 size: %d\n", my_string_get_size(hMy_string2));
	printf("hMy_string1 capacity: %d\n", my_string_get_capacity(hMy_string1));
	printf("hMy_string2 capacity: %d\n", my_string_get_capacity(hMy_string2));
	printf("Compare: %d\n", my_string_compare(hMy_string1, hMy_string2));

	my_string_destroy(&hMy_string1);
	my_string_destroy(&hMy_string2);

	return 0; 
}
