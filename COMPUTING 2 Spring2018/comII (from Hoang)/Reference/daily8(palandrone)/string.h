#include "status.h"


typedef void* STRING;


typedef struct string {
	int size;
	int capacity;
	char* char_arr;
} String;


STRING string_init_default(int capacity);
STRING string_init_c_string(STRING hString, char* s);
void string_destroy(STRING* pHString);
int string_compare(STRING string1, STRING string2);
int string_get_size(STRING hString);
int string_get_capacity(STRING hString);
char* string_at(STRING hString, int index);
char* string_c_str(STRING hString);
Boolean string_empty(STRING hString);
Boolean is_palindrome(STRING hString);
Status get_line(STRING hString, FILE* fp);
Status string_extraction(STRING hString, FILE* fp);
Status string_insertion(STRING hString, FILE* fp);
Status string_push_back(STRING hString, char item);
Status string_concat(STRING hResult, STRING hAppend);
Status string_pop_back(STRING hString);