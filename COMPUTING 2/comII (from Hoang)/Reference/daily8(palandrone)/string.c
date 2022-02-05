#include <stdio.h>
#include <stdlib.h>
#include "string.h"


STRING string_init_default(int capacity) {
	String* pString = (String*)malloc(sizeof(String));
	if (pString == NULL) {
		printf("Alloccation of pString failed.\n");
		exit(1);
	}
	pString->capacity = capacity;
	pString->size = 0;
	pString->char_arr = (char*)malloc(sizeof(char)*pString->capacity);
	if (pString->char_arr == NULL) {
		printf("Allocation of pString->char_arr failed.\n");
		exit(1);
	}
	return (STRING)pString;
}


STRING string_init_c_string(STRING hString, char* s) {
	int length;
	String* pString = (String*)hString;


	for (length = 0; s[length] != '\0'; length++);


	pString->capacity = length + 1;
	pString->size = length;
	pString->char_arr = (char*)malloc(sizeof(char)*pString->capacity);
	if (pString->char_arr == NULL) {
		printf("Allocation pString->char_arr failed.\n");
		exit(1);
	}
	for (length = 0; length <= pString->capacity; length++) {
		pString->char_arr[length] = s[length];
	}
	return pString;
}


int string_compare(STRING string1, STRING string2)
{
	int i, result;
	String* pString1 = (String*)string1;
	String* pString2 = (String*)string2;


	for (i = 0; i < pString1->size && i < pString2->size; i++)
	{
		result = pString1->char_arr[i] - pString2->char_arr[i];
	}


	return result;


}




void string_destroy(STRING* pHString) {


	String* pString = (String*)*pHString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return;
	}


	free(pString->char_arr); 
	free(pString);
	*pHString = NULL;


	return;
}


int string_get_size(STRING hString)
{
	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return FAILURE;
	}
	return (int)pString->size;
}


int string_get_capacity(STRING hString)
{
	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return FAILURE;
	}
	return (int)pString->capacity;
}


Status string_extraction(STRING hString, FILE* fp) {
	char c;
	int i = 0, n;
	char* pTemp;


	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return FAILURE;
	}


	n = fscanf(fp, " %c", &c);
	if (n != 1) {
		return FAILURE;
	}


	pString->size = 0;
	pString->char_arr[pString->size] = c;
	pString->size += 1;
	n = fscanf(fp, "%c", &c);


	while (n == 1) {
		if (pString->size >= pString->capacity)
		{
			pTemp = (char*)malloc(sizeof(char)*pString->capacity * 2);
			if (pTemp == NULL)
			{
				return FAILURE;
			}
			else
			{
				for (i = 0; i < pString->size; i++)
				{
					pTemp[i] = pString->char_arr[i];
				}
				free(pString->char_arr);
				pString->char_arr = pTemp;
				pString->capacity *= 2;
			}
		}


		pString->char_arr[pString->size] = c;
		pString->size += 1;
		n = fscanf(fp, "%c", &c);


		if (isspace(c) || n == EOF)
		{
			pString->char_arr[pString->size] = c;
			pString->size += 1;
			return SUCCESS;
		}
	}
	return SUCCESS;
}


Status string_insertion(STRING hString, FILE* fp) {
	int i = 0;


	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return FAILURE;
	}


	if (pString->char_arr[i] == '\0')
	{
		printf("Array is empty!\n");
		return FAILURE;
	}


	for (i = 0; i < pString->size; i++)
	{
		fputc(pString->char_arr[i], fp);
	}


	return SUCCESS;
}




Status string_push_back(STRING hString, char item)
{
	int i;
	char* pTemp;


	String* pString = (String*)hString;




	if (pString->size >= pString->capacity)
	{
		pTemp = (char*)malloc(sizeof(char)*pString->capacity * 2);
		if (pTemp == NULL)
		{
			return FAILURE;
		}
		else
		{
			for (i = 0; i < pString->size; i++)
			{
				pTemp[i] = pString->char_arr[i];
			}
			free(pString->char_arr);
			pString->char_arr = pTemp;
			pString->capacity *= 2;
		}
	}


	pString->char_arr[pString->size] = item;
	pString->size += 1;


	return SUCCESS;
}


Status string_pop_back(STRING hString)
{
	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return FAILURE;
	}


	pString->size -= 1;


	return SUCCESS;
}


char* string_at(STRING hString, int index)
{
	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return 0;
	}


	if (index > pString->size)
	{
		printf("Out of bound\n");
		return NULL;
	}


	return pString->char_arr[index];
}


char* string_c_str(STRING hString)
{
	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return 0;
	}


	return pString->char_arr;
}

Boolean is_palindrome(STRING hString)
{
	int i, index = 0, difference;
	char* temp_array;
	char c;
	String* pString = (String*)hString;


	temp_array = (char*)malloc(sizeof(char)*pString->size);


	for (i = 0; i < pString->size; i++)
	{
		if (isalpha(pString->char_arr[i]))
		{
			c = tolower(pString->char_arr[i]);
			temp_array[index] = c;
			index++;
		}
	}


	for (i = 0; index != 0; i++)
	{
		index--;
		difference = temp_array[i] - temp_array[index];
	}




	if (difference == 0)
	{
		return TRUE;
	}
	else
		return FALSE;
}


Boolean string_empty(STRING hString)
{
	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return FALSE;
	}


	if (pString->size == 0)
	{
		return TRUE;
	}


	return FALSE;
}




Status get_line(STRING hString, FILE* fp)
{
	char c;
	int i = 0, n;
	char* pTemp;


	String* pString = (String*)hString;
	if (pString == NULL) {
		printf("Allocation of pString failed.\n");
		return FAILURE;
	}


	n = fscanf(fp, "%c", &c);
	if (n != 1) {
		return FAILURE;
	}


	pString->size = 0;
	pString->char_arr[pString->size] = c;
	pString->size += 1;
	n = fscanf(fp, "%c", &c);


	while (n == 1) {
		if (pString->size >= pString->capacity)
		{
			pTemp = (char*)malloc(sizeof(char)*pString->capacity * 2);
			if (pTemp == NULL)
			{
				return FAILURE;
			}
			else
			{
				for (i = 0; i < pString->size; i++)
				{
					pTemp[i] = pString->char_arr[i];
				}
				free(pString->char_arr);
				pString->char_arr = pTemp;
				pString->capacity *= 2;
			}
		}


		pString->char_arr[pString->size] = c;
		pString->size += 1;
		n = fscanf(fp, "%c", &c);


		if (c == '\n' || n == EOF)
		{
			return SUCCESS;
		}
	}
	return SUCCESS;
}



Status string_concat(STRING hResult, STRING hAppend)
{
	char* pTemp;
	int i, j;


	String* pResult = (String*)hResult;
	if (pResult == NULL) {
		printf("Allocation of pResult failed.\n");
		return FAILURE;
	}
	String* pAppend = (String*)hAppend;
	if (pAppend == NULL) {
		printf("Allocation of pAppend failed.\n");
		return FAILURE;
	}


	for (i = 0; i < pAppend->size; i++)
	{
		if (pResult->size >= pResult->capacity)
		{
			pTemp = (char*)malloc(sizeof(char)*pResult->capacity * 2);
			if (pTemp == NULL)
			{
				return FAILURE;
			}
			else
			{
				for (j = 0; j < pResult->size; j++)
				{
					pTemp[j] = pResult->char_arr[j];
				}
				free(pResult->char_arr);
				pResult->char_arr = pTemp;
				pResult->capacity *= 2;
			}


		}
		pResult->char_arr[pResult->size] = pAppend->char_arr[i];
		pResult->size += 1;
	}


	if (pResult->size == pResult->capacity)
	{
		pTemp = (char*)malloc(sizeof(char)*pResult->capacity + 1);
		if (pTemp == NULL)
		{
			return FAILURE;
		}
		else
		{
			for (j = 0; j < pResult->size; j++)
			{
				pTemp[j] = pResult->char_arr[j];
			}
			free(pResult->char_arr);
			pResult->char_arr = pTemp;
			pResult->capacity += 1;
		}
	}
	pResult->char_arr[pResult->size] = '\0';
	return SUCCESS;
}



