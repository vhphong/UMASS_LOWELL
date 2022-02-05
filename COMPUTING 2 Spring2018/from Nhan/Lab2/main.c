#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string = NULL;
	hMy_string =  my_string_init_default();
//	my_string_destroy(&hMy_string);
//	hMy_string =  my_string_init_c_string("hi");

       	printf("%d\n",my_string_get_capacity(hMy_string));
       	printf("%d\n",my_string_get_size(hMy_string));
       	my_string_destroy(&hMy_string);
	MY_STRING str1 = NULL;
	MY_STRING str2 = NULL;
	str1 = my_string_init_c_string("apple");
	str2 = my_string_init_c_string("world");
	int i;
	i = my_string_compare(str2,str1);
	printf("%d\n",i);
	my_string_destroy(&str1);
	my_string_destroy(&str2);
	return 0;
}
