#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	MY_STRING hMy_string = NULL;
	FILE *fp;

	hMy_string = my_string_init_default();
	fp = fopen("dictionary.txt","r");
	//fp = fopen("simple.txt", "r");
	while(my_string_extraction(hMy_string,fp))
	{
	  //my_string_extraction(hMy_string, fp);
	  //printf("%d\n", my_string_get_size(hMy_string));
	    if( (my_string_get_size(hMy_string)) == 27 )
	    {
	      my_string_insertion(hMy_string,stdout);
	      printf("\n");
	     }
	    //if(fgetc(fp) == ' ')
	    //  printf("Found a space after the string\n");
	    
	}
//	if ((my_string_get_size(hMy_string)) == 27 )
//		{
//			my_string_insertion(hMy_string, stdout);
// 			printf("\n");
// 		}
	my_string_destroy(&hMy_string);
	fclose(fp);
	return 0;
}
