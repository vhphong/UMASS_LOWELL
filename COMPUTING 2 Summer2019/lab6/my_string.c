#include "my_string.h"

typedef struct my_string {
	int size; // number of characters in string
	int capacity;  // number of characters string can hold
	char* data;  // pointer to array of characters
} My_string;

MY_STRING my_string_init_default(void) {
	const int DEFAULT_SIZE = 0;
	const int DEFAULT_CAPACITY = 7;
	char* pData = NULL;
	My_string* pMy_string = NULL;
	pMy_string = (My_string*) malloc(sizeof(My_string));
	pData = (char*) malloc(DEFAULT_CAPACITY * sizeof(char));
	if (pMy_string != NULL && pData != NULL) {
		pMy_string->size = DEFAULT_SIZE;
		pMy_string->capacity = DEFAULT_CAPACITY;
		pMy_string->data = pData;
	}
	return pMy_string;
}

MY_STRING my_string_init_c_string(const char* c_string) {
	int i;
	int size;
	int capacity = 0;
	char* pData = NULL;
	My_string* pMy_string = NULL;
	while (c_string[capacity] != '\0') {
		++capacity;
	}
	size = capacity;
	++capacity; // increase by one so that capacity is one greater than size
	pMy_string = (My_string*) malloc(sizeof(My_string));
	pData = (char*) malloc(capacity * sizeof(char));
	if (pMy_string != NULL && pData != NULL) {
		pMy_string->size = size;
		pMy_string->capacity = capacity;
		for (i = 0; i < size; ++i) {
			pData[i] = c_string[i];
		}
		pMy_string->data = pData;
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

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
	char c;
	int i;
	char* pData;
	My_string* pMy_string = hMy_string;
	pMy_string->size = 0;  // allow program to replace data in string
	// check if anything is in file
	c = fgetc(fp);
	// keep reading whitespace until non-whitespace is reading
	while (c == EOF || c == ' ' || c== '\n' || c == '\t' || c == '\v' || c == '\f' || c == '\r'){
		if (c == EOF) {  // failure if only EOF is in file
			return FAILURE;
		}
		c = fgetc(fp);
	}
	while (c != ' ' && c != EOF && c!= '\n' && c != '\t' && c != '\v' && c != '\f' && c != '\r') {
		if (pMy_string->size == (pMy_string->capacity - 1)) {
			// reallocate space to fit new character
			pData = (char*) malloc((pMy_string->capacity + 1) * sizeof(char));
			if (pData == NULL) {
				return FAILURE;
			}
			for (i = 0; i <= pMy_string->size; ++i) {
				pData[i] = pMy_string->data[i];
			}
			// replace old data array with new one
			free(pMy_string->data);
			pMy_string->data = pData;
			pMy_string->capacity += 1;
		}
		pMy_string->data[pMy_string->size] = c;
		pMy_string->size += 1;
		c = fgetc(fp);
	}
	if (c != EOF) {
		ungetc(c, fp);  // put back whitespace character
	}
	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
	int i;
	My_string* pMy_string = hMy_string;
	for (i = 0; i <=   pMy_string->size; ++i) {
		fputc(pMy_string->data[i], fp);
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
	int i;
	char* pData;
	My_string* pMy_string = hMy_string;
	
	if (pMy_string->size == (pMy_string->capacity - 1)) {
		// reallocate space to fit new character
		// if reallocation is required, double the existing capacity
		pData = (char*) malloc((pMy_string->capacity * 2) * sizeof(char));
		if (pData == NULL) {
			return FAILURE;
		}
		for (i = 0; i <= pMy_string->size; ++i) {
			pData[i] = pMy_string->data[i];
		}
		// replace old data array with new one and destroy old one
		free(pMy_string->data);
		pMy_string->data = pData;
		pMy_string->capacity *= 2;
	}
	
	pMy_string->data[pMy_string->size] = item;
	pMy_string->size += 1;
	
	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string) {
	My_string* pMy_string = hMy_string;
	if (pMy_string->size == 0) {
		return FAILURE;
	}
	pMy_string->size -= 1;
	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index) {
	My_string* pMy_string = hMy_string;
	if (index >= 0 && index <= pMy_string->size) {
		return &(pMy_string->data[index]);
	}
	
	return NULL;
}

char* my_string_c_str(MY_STRING hMy_string) {
	My_string* pMy_string = hMy_string;
	pMy_string->data[pMy_string->size] = '\0';
	return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
	int i;
	char* pData = NULL;
	My_string* pResult = (My_string*) hResult;
	My_string* pAppend = (My_string*) hAppend;
	
	if (pResult->capacity <= pAppend->size + pResult->size) {
		// allocate more memory
		pData = malloc(sizeof(char) * (pResult->capacity + pAppend->size));
		if (pData == NULL) {
			return FAILURE;
		}
		for (i = 0; i <= pResult->size; ++i) {
			pData[i] = pResult->data[i];
		}
		pResult->capacity += pAppend->size;
		free(pResult->data);
		pResult->data = pData;
	}
	
	for(i = 0; i <= pAppend->size; ++i) {
		pResult->data[i + pResult->size] = pAppend->data[i];
	}
	
	pResult->size += pAppend->size;
	return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string) {
	My_string* pMy_string = hMy_string;
	if (pMy_string->size == 0) {
		return TRUE;
	}
	return FALSE;
}

/*
  Precondition: pLeft is the address of a MY_STRING handle containing a valid
  MY_STRING object address OR NULL. The value of Right must be the handle of a
  valid MY_STRING object
  Postcondition:  On Success pLeft will contain the address of a handle to a
  valid MY_STRING object that is a deep copy of the object indicated by Right.
  If the value of the handle at the address indicated by pLeft is originally
  NULL then the function will attempt to initialize a new object that is a deep
  copy of the object indicated by Right, otherwise the object indicated by the
  handle at the address pLeft will attempt to resize to hold the data in Right.
  On failure pLeft will be left as NULL and any memory that may have been used
  by a potential object indicated by pLeft will be returned to the freestore.
*/
void my_string_assignment(Item* pLeft, Item Right) {
	/*
	if(*pLeft != NULL)
		my_string_destroy(pLeft);
	my_string_init_c_string(my_string_c_str(Right));
	
	*/
	
	My_string* pMy_string_left = NULL;
	My_string* pMy_string_right = Right;
	int i;
	char* pData = NULL;
	
	if (*pLeft == NULL) {
		
		pMy_string_left = (My_string*) malloc(sizeof(My_string));
		pData = (char*) malloc((pMy_string_right->capacity) * sizeof(char));
		if (pMy_string_left != NULL && pData != NULL) {
			pMy_string_left->size = pMy_string_right->size;
			pMy_string_left->capacity = pMy_string_right->capacity;
			for (i = 0; i < pMy_string_right->size; ++i) {
				pData[i] = pMy_string_right->data[i];
			}
			pMy_string_left->data = pData;
			*pLeft = pMy_string_left;
		}
		else {
			if (pMy_string_left != NULL) {
				free(pMy_string_left);
				pLeft = NULL;
			}
			if (pData != NULL) {
				free(pData);
				pLeft = NULL;
			}
		}
	}
	else {
		/* 	  while(!my_string_empty(*pLeft)){
		  my_string_pop_back(*pLeft);
	  }
	  i = 0;
	  while(i<my_string_get_size(Right))
		  my_string_push_back(*pLeft, *my_string_at(Right, i));*/
		pMy_string_left = *pLeft; 
		//resize if needed, destroy if failure
		if (pMy_string_left->capacity < pMy_string_right->size) {
			//resize
			pData = (char*) malloc((pMy_string_right->capacity) * sizeof(char));
			if (pData == NULL) {
				return;
			}
			free(&pMy_string_left->data);
			pMy_string_left->data = pData;
			pMy_string_left->capacity = pMy_string_right->capacity;
		}
		pMy_string_left->size = pMy_string_right->size;
		for (i = 0; i < pMy_string_right->size; ++i) {
			pMy_string_left->data[i] = pMy_string_right->data[i];
		}
		*pLeft = pMy_string_left;
	}
}

void my_string_destroy(MY_STRING* phMy_string) {
	My_string* pMy_string = (My_string*) *phMy_string;
	free(pMy_string -> data);
	free(pMy_string);
	*phMy_string = NULL;
}