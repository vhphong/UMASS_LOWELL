#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	

 MY_STRING hMy_string = NULL;	
 MY_STRING lMy_string = NULL;
 MY_STRING rMy_string = NULL;
 hMy_string = my_string_init_c_string("and");
 lMy_string = my_string_init_c_string("shortest");
 rMy_string = my_string_init_c_string("long");
 printf("%d\n",my_string_get_capacity(hMy_string));
 printf("%d\n",my_string_get_size(hMy_string));
 printf("%d\n",my_string_compare(lMy_string, rMy_string));
 
 my_string_destroy(&hMy_string);
 my_string_destroy(&lMy_string);
 my_string_destroy(&rMy_string);
	

	return 0;
}
