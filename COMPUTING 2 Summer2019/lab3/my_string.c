#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my_string.h"

struct MyString{
	int size;
	int capacity;
	char* data;
};

typedef struct MyString my_string;

MY_STRING my_string_init_default(void){
	my_string* pString = malloc(sizeof(my_string));
	if (pString == NULL) return NULL;
	
	pString->size = 0;
	pString->capacity = 7;
	pString->data = malloc(sizeof(char)* pString->capacity);
	
	if (pString->data != NULL) return pString;
	
	free(pString);
	return NULL;
}

void my_string_destroy(MY_STRING* phMy_string){
	my_string* pMy_String = (my_string*) *phMy_string;
	free(pMy_String->data);
	free(pMy_String);
	*phMy_string = NULL;
}

MY_STRING my_string_init_c_string(const char* c_string){
	my_string* pString = malloc(sizeof(my_string));
	
	if (pString == NULL) return NULL;
	
	pString->size = strlen(c_string);
	pString->capacity = pString->size + 1;
	pString->data = malloc(sizeof(char)* pString->capacity);
	
	if (pString->data != NULL){
		strcpy(pString->data, c_string);
		return pString;
	}
	free(pString);
	return NULL;
}

int my_string_get_capacity(MY_STRING hMy_string){
	return ((my_string*) hMy_string)->capacity;
}

int my_string_get_size(MY_STRING hMy_string){
	return ((my_string*) hMy_string)->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string){
	my_string* l = (my_string*) hLeft_string;
	my_string* r = (my_string*) hRight_string;
	
	int diff = 0;
	
	int largerStringSize = my_string_get_size(hLeft_string) >= my_string_get_size(hRight_string)?
								my_string_get_size(hLeft_string) : my_string_get_size(hRight_string);
	
	for (int i=0; i<largerStringSize; ++i){
		if (l->data[i] != r->data[i]){
			++diff;
		}
		// diff += l->data[i] - (r->data[i]);
		
	}
	
	return diff;
}


Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	my_string* pString = (my_string*) hMy_string;
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
		if(pString->size >= pString->capacity)
		{
			printf("%c ***\n", c);
			printf("%d - ", pString->size);
			printf("%d \n", pString->capacity);

			temp = (char *) malloc(sizeof(char) * 2 * pString->capacity);

			if(temp == NULL)
			{
				return FAILURE;
			}
			for(int i=0; i < pString->size; i++)
			{
				temp[i] = pString->data[i];
			}

			free(pString->data);
			pString->data = temp;
			pString->capacity *= 2;
		}

		pString->data[count] = c;
		count++;

		c = fgetc(fp);
		pString->size = count;
	}

	if(c == ' ')
	{
		ungetc(c, fp); 
	}

	return SUCCESS;
}
 

Status my_string_insertion(MY_STRING hMy_string, FILE *fp)
{
	my_string* pString = (my_string*) hMy_string;
	int count = 0;

	for(count=0; count < pString->size; count++)
	{
		fputc(pString->data[count], fp);
	}

	if(count == 0)
	{
		return FAILURE;
	}
	return SUCCESS;
}
