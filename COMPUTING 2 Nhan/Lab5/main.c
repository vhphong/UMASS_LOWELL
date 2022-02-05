
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string1 = NULL;
	
	MY_STRING hMy_string2 = NULL;
	
	hMy_string1 = my_string_init_c_string("The");
	my_string_insertion(hMy_string1,stdout);
	printf("\n");
	
	hMy_string2 = my_string_init_c_string("comp");
	
	my_string_push_back(hMy_string1,'c');
	my_string_insertion(hMy_string1,stdout);
	printf("\n");
	
	my_string_pop_back(hMy_string1);
	my_string_insertion(hMy_string1,stdout);
	printf("\n");
 	char *temp;
	temp = my_string_at(hMy_string1,2);
	printf("%c\n",*temp);
	
	temp = my_string_c_str(hMy_string1);
	printf("%s\n",temp);
	 
 	my_string_concat(hMy_string1,hMy_string2);
	my_string_insertion(hMy_string1,stdout);
	printf("\n");
	printf("%d, %d \n",my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
	printf("\n");

	if(my_string_empty(hMy_string1) == TRUE)
	{
		printf("Hen xui\n");
	}
	else
	{
		printf("Viet dep trai\n");
	} 
	my_string_destroy(&hMy_string1);
	my_string_destroy(&hMy_string2);
	return 0;
}

