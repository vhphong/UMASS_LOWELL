#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include <string.h>
struct string
{
  int size;
  int capacity;
  char *data;
};

typedef struct string String;
typedef String *Stringptr;

MY_STRING my_string_init_default(void)
{
	Stringptr pString = (Stringptr)malloc(sizeof(String));
	if(pString != NULL)
		
	{
		pString->size = 0;
		pString->capacity = 7;
		pString->data =  (char *)malloc(sizeof(char) * pString->capacity);
		if(pString->data == NULL)
		{
			free(pString);
			pString = NULL;
		}
    }
	return (MY_STRING)pString;
}

void my_string_destroy(MY_STRING* phMy_string)
{
	Stringptr pString = (Stringptr) *phMy_string;
	if(pString->data != NULL)
	{
		free(pString->data);
	}
	if(pString != NULL)
	{
		free(pString);
	}
	*phMy_string = NULL;
}
MY_STRING my_string_init_c_string(const char* c_string)
{
	Stringptr pString = (Stringptr)malloc(sizeof(String));
	int len = 0;
	while(c_string[len] != '\0')
	{  
		len++;
	}
	if(pString != NULL)
	{
		pString->size = len;
		pString->capacity = len + 1;
		pString->data = (char *)malloc(sizeof(char) * pString->capacity);
		if(pString->data == NULL)
		{
			free(pString);
			pString = NULL;
		}
	}
	int i;
	for(i = 0; i < pString->size; i++)
	  {
	    pString->data[i] = *(c_string + i);
	  }
	return (MY_STRING)pString;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
	Stringptr pString = (Stringptr) hMy_string;
	return pString->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	Stringptr pString = (Stringptr) hMy_string;
	return pString->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  
  Stringptr left = (Stringptr) hLeft_string;  
  Stringptr right = (Stringptr) hRight_string;
  int i = 0;
  while(i < left->size && i < right->size)
    {
      if(left->data[i] != right->data[i])
	return left->data[i] - right->data[i];
      else
	i++;
    }
  return left->size - right->size;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	Stringptr pString = (Stringptr) hMy_string;
	char c = fgetc(fp);
	int i, count = 0;
	char *temp;
  
	if ( c == EOF)
	{
		return FAILURE;
	}
	while ( c == ' ' || c == '\n')
	{
		c = fgetc(fp);
	}
	while ( c != EOF  && c !=' ' && c != '\n')
	{
		pString->data[count] = c;
		count++;
		pString->size = count;
		if (pString->size >= pString->capacity)
		{
			temp = (char*)malloc(sizeof(char) * 2 * pString->capacity);
			if (temp == NULL)
			{
				return FAILURE;
			}
			for(i = 0; i < pString->size; i++)
			{
				temp[i] = pString->data[i];
			}
			free(pString->data);
			pString->data = temp;
			pString->capacity *= 2;
		}
		  c = fgetc(fp);
	}
	
	if(c != ' ' && count == 0)
	{
		return FAILURE;
	}
	else if (count == 0)
	{
		return FAILURE;
	}
	else
	{
		ungetc(c,fp);
		pString->data[count] = '\0';
		return SUCCESS;
	}
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	Stringptr pString = (Stringptr)hMy_string;
	int i = 0;
	if(fp == NULL)
	{
		return FAILURE;
	}
	for(i = 0; i < pString->size ; i++)
	{
		int ch = (pString->data[i]);
		if(fputc(ch, fp) == EOF)
		{
			return FAILURE;
		}
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	Stringptr pString = (Stringptr)hMy_string;
	char *temp;
	int i;
	pString->data[pString->size] = item;
	pString->size++;
	if(pString->size >= pString->capacity)
    {
		temp = (char*)malloc(sizeof(char) * 2 * pString->capacity);
		if(temp == NULL)
		{
			return FAILURE;
		}
		for(i = 0; i < pString->size; i++)
		{
			temp[i] = pString->data[i];
		}
		free(pString->data);
		pString->data = temp;
		pString->capacity *= 2;
    }
  
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
  Stringptr pString = (Stringptr)hMy_string;
  if(pString->size <= 0 || pString == NULL)
  {
	return FAILURE;
  }
  pString->size--;
  return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
  Stringptr pString = (Stringptr)hMy_string;
  if(pString->data == NULL || index > pString->size || index < 0 )
    return NULL;
  return &(pString->data[index]);
}

char* my_string_c_str(MY_STRING hMy_string)
{
  Stringptr pString = (Stringptr)hMy_string;
  if (pString == NULL)
	  return NULL;
  pString->data[pString->size] = '\0';
  return pString->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	Stringptr rString = (Stringptr)hResult;
	Stringptr aString = (Stringptr)hAppend;
	int i;
	for(i = 0; i < aString->size; i++)
    {
		my_string_push_back(rString, aString->data[i]);
		if(rString->data[rString->size - 2] == rString->data[rString->size -1])
		{
			return FAILURE;
		}
    }
	if (rString->size >= rString->capacity)
    {
		return FAILURE;
	}
	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string)
{
  Stringptr pString = (Stringptr)hMy_string;
  if(pString->size == 0)
  {
	return TRUE;
  }
  return FALSE;
}
