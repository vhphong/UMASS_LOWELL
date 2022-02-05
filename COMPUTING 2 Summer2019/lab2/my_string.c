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
	my_string* str = malloc(sizeof(my_string));
	if (str == NULL) return NULL;
	
	str->size = 0;
	str->capacity = 7;
	str->data = malloc(sizeof(char)* str->capacity);
	
	if (str->data != NULL) return str;
	
	free(str);
	return NULL;
}

void my_string_destroy(MY_STRING* phMy_string){
	my_string* pMy_String = (my_string*) *phMy_string;
	free(pMy_String->data);
	free(pMy_String);
	*phMy_string = NULL;
}

MY_STRING my_string_init_c_string(const char* c_string){
	my_string* str = malloc(sizeof(my_string));
	
	if (str == NULL) return NULL;
	
	str->size = strlen(c_string);
	str->capacity = str->size + 1;
	str->data = malloc(sizeof(char)* str->capacity);
	
	if (str->data != NULL){
		strcpy(str->data, c_string);
		return str;
	}
	free(str);
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
	
	// for (int i=0; i<my_string_get_size(hLeft_string) && i<my_string_get_size(hRight_string); ++i){
	for (int i=0; i<largerStringSize; ++i){
		if (l->data[i] != r->data[i]){
			++diff;
		}
		// diff += l->data[i] - (r->data[i]);
		
	}
	
	return diff;
}