#include "my_string.h"
#include <stdio.h>
#include <stdlib.h>

struct my_string
{
	int size;
	int capacity;
	char* data;
};

typedef struct my_string My_String;

MY_STRING my_string_init_default(void)
{
	My_String * pMy_string;
	pMy_string = (My_String*)malloc(sizeof(My_String));
	if(pMy_string != NULL)
	{
		pMy_string->size = 0;
		pMy_string->capacity = 7;
		pMy_string->data = malloc(sizeof(char)*pMy_string->capacity);
		if(pMy_string->data == NULL)
		{
			printf("Object half created");
			free(pMy_string);
			pMy_string = NULL;
		}
	}
	return pMy_string;
}

void my_string_destroy(MY_STRING* phMy_string)
{
	My_String* pMy_string = (My_String*)*phMy_string;
	free(pMy_string->data);
	free(pMy_string);
	*phMy_string = NULL;
	return;
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	My_String *pMy_string;
	pMy_string = (My_String*)malloc(sizeof(My_String));
	int i=0;
	while(c_string[i] != '\0')
	{
		i++;
	}
	if(pMy_string != NULL)
	{
		pMy_string->size = i;
		pMy_string->capacity = i+1;
		pMy_string->data = malloc(sizeof(char)*pMy_string->capacity);
		i=0;
		while(c_string[i] != '\0')
		{
			pMy_string->data[i] = c_string[i];
			i++;
		}
		if(pMy_string->data == NULL)
		{
			printf("Object half created");
			free(pMy_string);
			pMy_string = NULL;
			return NULL;
		}
		
	}	

	return pMy_string;
}

int my_string_get_capacity(MY_STRING hMy_string)
{

	My_String *pMy_string = (My_String*)hMy_string; 
	return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	My_String *pMy_string = (My_String*)hMy_string;
	return pMy_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_String *pLeft_String = hLeft_string;
	My_String *pRight_String = hRight_string;

	if(pLeft_String->size > pRight_String->)
	{
		for(i=0;i <= pLeft_string->size; i++)
		{
			if(pLeft_string->data[i] < pRight_string->data[i])
			{
				return -1;
			}
			else if(if(pLeft_string->data[i] > pRight_string->data[i])
			{
				return 1;
			}
		}
		return 0;
	}
	else
	{
		for(i = 0;i <= pLeft_string->size; i++)
		{
			if(pLeft_string->data[i] < pRight_string->data[i])
			{
				return -1;
			}
			else if(pLeft_string->data[i] > pRight_string->data[i])
			{
				return 1;
			}
		}
		return 0;

	}

}


