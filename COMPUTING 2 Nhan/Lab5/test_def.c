#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_default();
	if(hString == NULL)
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_init_default_returns_nonNULL\n""my_string_init_default returns NULL", length);
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
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n""Did not receive 0 from get_size after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_default_returns_0\n", length);
	}
	my_string_destroy(&hString);
	return status;
}
Status test_get_capacity_on_init_default_returns_7(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_capacity(hString) != 7)
	{
		status = FAILURE;
		printf("Expected a size of 7 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n""Did not receive 7 from get_capacity after init_default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_default_returns_7\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_init_c_string_returns_nonNULL(char* buffer, int length)
{
	MY_STRING hString = NULL;
	hString = my_string_init_c_string("The");
	if(hString == NULL)
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_init_c_string_returns_nonNULL\n""my_string_init_c_string returns NULL", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy(&hString);
		strncpy(buffer, "test_init_c_string_returns_nonNULL\n", length);
		return SUCCESS;
	}
}
Status test_get_size_on_init_c_string_returns_non_0(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_c_string("The");
	if(my_string_get_size(hString) == 0)
	{
		status = FAILURE;
		printf("Expected non 0 size but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_get_size_on_init_c_string_returns_non_0\n""Did not receive non 0 from get_size after init_c_string\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_size_on_init_c_string_returns_non_0\n", length);
	}
	my_string_destroy(&hString);
	return status;
}
Status test_get_capacity_on_init_c_string_compare_with_size(char* buffer, int length)
{
	MY_STRING hString = NULL;
	Status status;
	hString = my_string_init_default();
	if(my_string_get_capacity(hString) <= my_string_get_size(hString))
	{
		status = FAILURE;
		printf("Expected a size less than a capacity but got bigger\n");
		strncpy(buffer, "test_get_capacity_on_init_c_string_compare_with_size\n""The capacity is less than the size\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_get_capacity_on_init_c_string_compare_with_size\n", length);
	}
	my_string_destroy(&hString);
	return status;
}

Status test_my_string_extraction_return_nonNULL(char* buffer, int length)
{
	MY_STRING hMy_string = NULL;
	FILE *fp;
	hMy_string = my_string_init_default();
	fp = fopen("dictionary.txt","r");
	my_string_extraction(hMy_string,fp);
	if(hMy_string == NULL)
	{
		my_string_destroy(&hMy_string);
		strncpy(buffer, "test_my_string_extraction_return_nonNULL\n""my_string_extraction returns NULL", length);
		return FAILURE;
	}
	else
	{
		my_string_destroy(&hMy_string);
		strncpy(buffer, "test_my_string_extraction_return_nonNULL\n", length);
		return SUCCESS;
	}
}

Status test_my_string_insertion_return_SUCCESS(char* buffer, int length)
{
	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_c_string("The");
	Status status;
	status = my_string_insertion(hMy_string,stdout);
	if (status == FAILURE)
	{
		printf("Can't print out\n");
		strncpy(buffer,"test_my_string_insertion_return_SUCCESS\n""Can't print out\n",length);
	}
	else
	{
		my_string_destroy(&hMy_string);
		strncpy(buffer,"test_my_string_insertion_return_SUCCESS\n",length);
	}
	return status;
}

Status test_my_string_push_back_return_SUCCESS(char* buffer, int length)
{
	MY_STRING hMy_string = NULL;
	hMy_string = my_string_init_c_string("The");
	Status status;
	status = my_string_push_back(hMy_string,'c');
	if (status == FAILURE)
	{
		printf("Can't push in\n");
		strncpy(buffer,"test_my_string_push_back_return_SUCCESS\n""Can't push in\n",length);
	}
	else
	{
		my_string_destroy(&hMy_string);
		strncpy(buffer,"test_my_string_push_back_return_SUCCESS\n",length);
	}
	return status;
}