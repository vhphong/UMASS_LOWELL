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

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	struct S_MyString *my_string = (struct S_MyString*) hMy_string;
	char c = fgetc(fp);
	int count = 0; 
	char *temp;

	if(c == EOF)
	{
		return FAILURE;
	}

	while(c == ' ')
	{
		c = fgetc(fp);
	}

	while(c != EOF && c != ' ' && c != '\n')
	{
		// printf("%c ", c);
		if(my_string->size >= my_string->capacity)
		{
			printf("%c ***\n", c);
			printf("%d - ", my_string->size);
			printf("%d \n", my_string->capacity);

			temp = (char *) malloc(sizeof(char) * 2 * my_string->capacity);

			if(temp == NULL)
			{
				return FAILURE;
			}
			for(int i=0; i < my_string->size; i++)
			{
				temp[i] = my_string->c_string[i];
			}

			free(my_string->c_string);
			my_string->c_string = temp;
			my_string->capacity *= 2;
		}

		my_string->c_string[count] = c;
		count++;

		c = fgetc(fp);
		my_string->size = count;
	}

	if(c == ' ')
	{
		ungetc(c, fp); 
	}

	return SUCCESS;
}
 

Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
	struct S_MyString *my_string = (struct S_MyString*) hMy_string;
	int count = 0;

	for(count=0; count < my_string->size; count++)
	{
		fputc(my_string->c_string[count], fp);
	}

	if(count == 0)
	{
		return FAILURE;
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
	struct S_MyString *pString = (struct S_MyString*) hMy_string;
	char* temp;
	int i;
	if (pString->size >= pString->capacity)
	{
		temp = (char*)malloc(sizeof(char) * 2 * pString->capacity);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pString->size; i++)
		{
			temp[i] = pString->c_string[i];
		}
		free(pString->c_string);
		pString->c_string = temp;
		pString->capacity *= 2;
	}
	pString->c_string[pString->size] = item;
	pString->size++;
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
	struct S_MyString *pString = (struct S_MyString*) hMy_string;
	if (pString->size <= 0)
	{
		return FAILURE;
	}
	pString->size --;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	struct S_MyString *pString = (struct S_MyString*) hMy_string;
	if (index < 0 || index >= pString->size)
	{
		return NULL;
	}
	return &pString->c_string[index];
}


char* my_string_c_str(MY_STRING hMy_string)
{

	struct S_MyString *pString = (struct S_MyString*) hMy_string;
	char* temp;
	int i;
	if (pString->size >= pString->capacity)
	{
		temp = (char*) malloc(sizeof(char) *(pString->capacity + 1));
		if (temp == NULL)
		{
			return NULL;
		}
		for (i = 0; i < pString->size; i++)
		{
			temp[i] = pString->c_string[i];
		}
		free(pString->c_string);
		pString->c_string = temp;
		pString->capacity = (pString->capacity+1);
	}
	pString->c_string[pString->size] ='\0';
	return &pString->c_string[0];
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	struct S_MyString *pResult = (struct S_MyString*) hResult;
	struct S_MyString *pAppend = (struct S_MyString*) hAppend;
	char* c = NULL;
	int i = 0;
	if(pAppend->size == 0)
	{
		return FAILURE;
	}
	else
	{
		for(i=0; i < pAppend->size; i++)
		{
			c = my_string_at(hAppend, i);
			my_string_push_back(pResult, c[0]);
		}
		return SUCCESS;
	}
}

Boolean my_string_empty(MY_STRING hMy_string)
{
	struct S_MyString *pString = (struct S_MyString*) hMy_string;
	if (pString->size==0)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}	

