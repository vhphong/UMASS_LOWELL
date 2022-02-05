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


Status test_get_size_on_init_default_returns_0(char* buffer, int length) 
{
	MY_STRING hString = NULL; 
	Status status;

	hString = my_string_init_default();

	if(my_string_get_size(hString) != 0) 
	{
		status = FAILURE;
		printf("Expected a size of 0 but got %d\n", my_string_get_size(hString)); 
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
				"Did not receive 0 from get_size after init_default\n", length);
	} 
	else 
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length); 
	}

	my_string_destroy(&hString);
	return status; 
}

Status test_my_string_destroy(char *buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	
	hString = my_string_init_c_string("hello");
	my_string_destroy(&hString);
	
	if(hString == NULL)
	{
		strncpy(buffer, "test_my_string_destroy\n", length);
		status = SUCCESS;
	}	
	else
	{
		status = FAILURE;
		printf("Expected a NULL but got %s\n", my_string_c_str(hString)); 
		strncpy(buffer, "test_my_string_destroy, Did not destroy string\n", length);
	}

	return status;
}

Status test_my_string_at(char *buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	char *c;

	hString = my_string_init_c_string("hello");
	c = my_string_at(hString, 4);

	if(*c == 'o')
	{
		status = SUCCESS;
		strncpy(buffer, "test_my_string_at\n", length);
	}	
	else
	{
		status = FAILURE;
		printf("Expected a char 'o' but got %c\n", *c); 
		strncpy(buffer, "test_my_string_at, Did not receive exact char\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

