#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
 MY_STRING hMy_string = NULL;
 FILE* fp;
 hMy_string = my_string_init_default();
 fp = fopen("dictionary.txt", "r");
 printf("file was opened\n" );

 while(my_string_extraction(hMy_string, fp))
 {
 	
	if( (my_string_get_size(hMy_string)) == 5){
 		my_string_insertion(hMy_string, stdout);
 		printf("\n");
 	}

 	if(fgetc(fp)== ' '){
		printf("found a space after the string!\n");	
 	}
 }

 fclose(fp);

 fp = fopen("dictionary.txt", "r");
printf("\n");

while(my_string_extraction(hMy_string, fp)){

 if ((my_string_get_size(hMy_string)) == 29 ){
 	my_string_insertion(hMy_string, stdout);
 	printf("\n");
 } // end if
}
 my_string_destroy(&hMy_string);
 fclose(fp);
 return 0;
} // end main

