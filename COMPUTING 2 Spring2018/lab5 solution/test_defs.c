#include <string.h>
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length) 
{
	MY_STRING hString = NULL; 
	hString = my_string_init_default();

	if(hString == NULL) 
	{
		strncpy(buffer, "test_init_default_returns_nonNULL\n" 
			"my_string_init_default returns NULL", length);
		return FAILURE; 
	}
	else 
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_init_default_returns_nonNULL\n", length); 
		return SUCCESS;
	} 
}

