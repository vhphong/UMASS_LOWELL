#include <stdio.h> 
#include <stdlib.h> 
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string = NULL;
	MY_STRING hMy_string2 = NULL;

	hMy_string = my_string_init_c_string("UMass");
	hMy_string2 = my_string_init_c_string("Lowell");

	printf("my_string_c_str: \n");
	printf("%s\n", my_string_c_str(hMy_string));
	printf("%s\n", my_string_c_str(hMy_string2));

	printf("my_string_at: \n");
	printf("%s\n", my_string_at(hMy_string, 0));
	printf("%s\n", my_string_at(hMy_string2, 0));

	printf("my_string_concat: \n");
	my_string_concat(hMy_string, hMy_string2);
	printf("%s\n", my_string_c_str(hMy_string));
	printf("%s\n", my_string_c_str(hMy_string2));

	printf("my_string_pop_back: \n");
	for (int i = 0; i < 5; i++)
	{
		my_string_pop_back(hMy_string);
		printf("%s\n", my_string_c_str(hMy_string));
	}

	printf("my_string_push_back: \n");
	my_string_push_back(hMy_string, '!');
	printf("%s\n", my_string_c_str(hMy_string));

	if (my_string_empty(hMy_string) == TRUE)
	{
		printf("my_string_empty: \n");
		printf("hMy_string is empty\n");
	}

	my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);

	return 0;
}
