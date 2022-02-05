#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	
	
	MY_STRING hMy_string = NULL;
	
	
	
		
	
	hMy_string = my_string_init_default();
	if(hMy_string == NULL)
	{
		printf("Failed to allocate memory\n");
		exit(1);
	}
	
	


		

	 hMy_string = my_string_init_c_string("hi");
 lMy_string = my_string_init_c_string("short");
 rMy_string = my_string_init_c_string("longer");
printf("%d\n",my_string_get_capacity(hMy_string));
 printf("%d\n",my_string_get_size(hMy_string));
 printf("%d\n",my_string_compare(lMy_string, rMy_string));
 my_string_destroy(&hMy_string);
 my_string_destroy(&lMy_string);
 my_string_destroy(&rMy_string);





	
	my_string_destroy(&hMy_string);



	return 0;
}
