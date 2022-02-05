#include <stdio.h> 
#include <stdlib.h> 
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string1 = NULL;
	MY_STRING hMy_string2 = NULL;

	hMy_string1 = my_string_init_c_string("UMass");
	hMy_string2 = my_string_init_c_string("Lowell");

	printf("-----\nmy_string_c_str: \n");
	printf("%s\n", my_string_c_str(hMy_string1));
	printf("%s\n", my_string_c_str(hMy_string2));

	printf("-----\nmy_string_at: \n");
	printf("%s\n", my_string_at(hMy_string1, 1));
	printf("%s\n", my_string_at(hMy_string2, 4));

	printf("-----\nmy_string_concat: \n");
	my_string_concat(hMy_string1, hMy_string2);
	printf("hMy_string1: %s\n", my_string_c_str(hMy_string1));
	printf("hMy_string2: %s\n", my_string_c_str(hMy_string2));

	printf("-----\nmy_string_pop_back: \n");
	for (int i = 0; i < 15; i++)
	{
		my_string_pop_back(hMy_string1);
		printf("%s\n", my_string_c_str(hMy_string1));
	}

	printf("-----\nmy_string_push_back: \n");
	my_string_push_back(hMy_string1, '!');
	printf("%s\n", my_string_c_str(hMy_string1));

	if (my_string_empty(hMy_string1) == TRUE)
	{
		printf("my_string_empty: \n");
		printf("hMy_string1 is empty\n");
	}
	
	if (my_string_empty(hMy_string2) == TRUE)
	{
		printf("my_string_empty: \n");
		printf("hMy_string2 is empty\n");
	}
	
	my_string_destroy(&hMy_string1);
	my_string_destroy(&hMy_string2);

	return 0;
}
