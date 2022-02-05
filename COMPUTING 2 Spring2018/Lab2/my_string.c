#include "my_string.h"

typedef struct my_string {
  int size; // number of characters in string
  int capacity;  // number of characters string can hold
  char* data;  // pointer to array of characters
} My_string;

MY_STRING my_string_init_default(void) {
  const int DEFAULT_SIZE = 0;
  const int DEFAULT_CAPACITY = 7;
  char* pString = NULL;
  My_string* pMy_string = NULL;
  pMy_string = (My_string*) malloc(sizeof(My_string));
  pString = (char*) malloc(DEFAULT_CAPACITY * sizeof(char));
  if (pMy_string != NULL && pString != NULL) {
    pMy_string->size = DEFAULT_SIZE;
    pMy_string->capacity = DEFAULT_CAPACITY;
    pMy_string->data = pString;
  }
  return pMy_string;
}

MY_STRING my_string_init_c_string(const char* c_string) {
  int i;
  int size;
  int capacity = 0;
  char* pString = NULL;
  My_string* pMy_string = NULL;
  while (c_string[capacity] != '\0') {
    ++capacity;
  }
  size = capacity;
  ++capacity; // increase by one to hold null character
  pMy_string = (My_string*) malloc(sizeof(My_string));
  pString = (char*) malloc(capacity * sizeof(char));
  if (pMy_string != NULL && pString != NULL) {
    pMy_string->size = size;
    pMy_string->capacity = capacity;
    for (i = 0; i < size; ++i) {
      pString[i] = c_string[i];
    }
    pMy_string->data = pString;
  }
  return pMy_string;
}

int my_string_get_capacity(MY_STRING hMy_string) {
  My_string* pMy_string = hMy_string;
  return pMy_string->capacity;
}

int my_string_get_size(MY_STRING hMy_string) {
  My_string* pMy_string = hMy_string;
  return pMy_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string) {
  int i;
  int retval = 0;
  My_string* pLeft_string = hLeft_string;
  My_string* pRight_string = hRight_string;
  if (pLeft_string->size <= pRight_string->size) {
    for (i = 0; i < pLeft_string->size && retval == 0; ++i) {
      retval += ((int) pLeft_string->data[i] - (int) pRight_string->data[i]);
    }
    while (i < pRight_string->size && retval == 0) {
      retval -= (int) pRight_string->data[i];
      ++i;
    }
  }
  else {
    for (i = 0; i < pRight_string->size && retval == 0; ++i) {
      retval += (int) pLeft_string->data[i] - (int) pRight_string->data[i];
    }
    while (i < pLeft_string->size && retval == 0) {
      retval += (int) pLeft_string->data[i];
      ++i;
    }
  }
  return retval;
}












void my_string_destroy(MY_STRING* phMy_string) {
  My_string* pMy_string = (My_string*) *phMy_string;
  free(pMy_string -> data);
  free(pMy_string);
  *phMy_string = NULL;
}