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
	free(pString->data);
	free(pString);
	*phMy_string = NULL;
}
MY_STRING my_string_init_c_string(const char* c_string)
{
	Stringptr pString = (Stringptr)malloc(sizeof(String));
	int len = 0;
	while(c_string[len] != '\0')
	  len++;
	if(pString != NULL)
	{
		pString->size = len;
		pString->capacity = strlen(c_string)+1;
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
    return FAILURE;
  while ( c == ' ' || c == '\n')
    c = fgetc(fp);
  while ( c != EOF  && c !=' ' && c != '\n')
    {
      pString->data[count] = c;
      count++;
      pString->size = count;
      if (pString->size >= pString->capacity)
	{
	  temp = (char*)malloc(sizeof(char) * 2 * pString->capacity);
	  if (temp == NULL)
	    return FAILURE;
	  for(i = 0; i < pString->size; i++)
	    temp[i] = pString->data[i];
	  free(pString->data);
	  pString->data = temp;
	  pString->capacity *= 2;
	}
      c = fgetc(fp);
    }
  pString->data[count] = '\0';
  if(c == ' ' && count!=0)
    {
      ungetc(c,fp);
      return SUCCESS;
    }
  if (count == 0)
    return FAILURE;    
}
Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  Stringptr pString = (Stringptr)hMy_string;
  int i = 0;
  if(fp == NULL)
    return FAILURE;
  while(pString->data[i] != NULL)
    {
      fputc(pString->data[i], fp);
      i++;
    }
}
