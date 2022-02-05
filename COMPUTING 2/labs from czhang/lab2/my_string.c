#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

struct S_MyString
{
	int size, capacity;
	char* c_string;
};

typedef struct S_MyString my_string;

MY_STRING my_string_init_default(void)
{
	
	struct S_MyString* s_string = malloc(sizeof(struct S_MyString));
	
	if(s_string == NULL)
	{
		return NULL;
	}

	s_string->size = 0;
	s_string->capacity = 7;
	s_string->c_string = malloc(sizeof(char) * s_string->capacity);

	if(s_string->c_string != NULL)
	{
		return s_string;
	}

	free(s_string);
	return NULL;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	struct S_MyString* s_string = malloc(sizeof(struct S_MyString));

	if(s_string == NULL)
	{
		return NULL;
	}

	s_string->size = strlen(c_string);
	s_string->capacity = s_string->size + 1;
	s_string->c_string = malloc(sizeof(char) * s_string->capacity);

	if(s_string->c_string != NULL)
	{
		strcpy(s_string->c_string, c_string);
		return s_string;
	}

	free(s_string);
	return NULL;
}

void my_string_destroy(MY_STRING* pMy_string)
{
	free(((struct S_MyString*) *pMy_string)->c_string);
	free((struct S_MyString*) *pMy_string);
	*pMy_string = NULL;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	return ((struct S_MyString*) hMy_string)->capacity;
}


int my_string_get_size(MY_STRING hMy_string)
{
	return ((struct S_MyString*) hMy_string)->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	my_string* left = (my_string*) hLeft_string;
	my_string* right = (my_string*) hRight_string;

	for(int i=0; i<my_string_get_size(hLeft_string) && i<my_string_get_size(hRight_string); i++ )
	{
		if(left->c_string[i] != right->c_string[i])
		{
			// printf("%d\n", left->c_string[i]);
			// printf("%d\n", right->c_string[i]);
			return left->c_string[i] - right->c_string[i];
		}
	}

	return my_string_get_size(hLeft_string) - my_string_get_size(hRight_string);
}

