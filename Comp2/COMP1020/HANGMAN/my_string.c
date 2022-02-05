#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

struct my_string {
  	int size; 
  	int capacity;  
  	char* data;  
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
    My_string* pMy_string;
    pMy_string = (My_string*)malloc(sizeof(My_string));
    if(pMy_string != NULL)
    {
        pMy_string->size = 0;
        pMy_string->capacity = 7;
        pMy_string->data = malloc(sizeof(char)*pMy_string->capacity);
        if(pMy_string->data == NULL)
        {
        	printf("Unable to allocate memory.");
            free(pMy_string);
            free(pMy_string->data);
            pMy_string = NULL;
        }
    }
    return pMy_string;
}

MY_STRING my_string_init_c_string(const char* c_string) {
  	My_string *pMy_string;
	pMy_string = (My_string*)malloc(sizeof(My_string));
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
		if(pMy_string->data == NULL)
		{
			free(pMy_string);
			pMy_string = NULL;
			return NULL;
		}
		for (i = 0; i < pMy_string->size; ++i) 
		{
			pMy_string->data[i] = c_string[i];
		}
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
	int result = 0;
	My_string* pLeft_string = hLeft_string;
	My_string* pRight_string = hRight_string;
	if (pLeft_string->size <= pRight_string->size) {
	    for (i = 0; i < pLeft_string->size && result == 0; ++i) {
	      result += ((int) pLeft_string->data[i] - (int) pRight_string->data[i]);
	    }
	    while (i < pRight_string->size && result == 0) {
	      result -= (int) pRight_string->data[i];
	      ++i;
	    }
	}
  	else {
    	for (i = 0; i < pRight_string->size && result == 0; ++i) {
      	result += (int) pLeft_string->data[i] - (int) pRight_string->data[i];
    	}
    	while (i < pLeft_string->size && result == 0) {
      		result += (int) pLeft_string->data[i];
     		 ++i;
    	}
  	}
  	return result;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp) {
  	My_string* pMy_string = hMy_string;
	char c;
	int i;
	char* pTemp;
	pMy_string->size = 0;
	c= fgetc(fp);
	
	while (c == EOF || c == ' ' || c == '\n' || c == '\t')
	{
		if (c == EOF){
			return FAILURE;
		}
		c = fgetc(fp);
	}
	
	while(c != EOF && c != ' ' && c != '\n' && c != '\t')
	{
		if (pMy_string->size >= (pMy_string->capacity - 1)){
		pTemp = (char*)malloc(sizeof(char)*2*pMy_string->capacity); 
			if (pTemp == NULL)
			{
				return FAILURE; 
			}
			for (i = 0; i <= pMy_string->size; i++){  	
				pTemp[i] = pMy_string->data[i]; 
			}	
			free(pMy_string->data); 
		    	pMy_string->capacity *= 2;
			pMy_string->data = pTemp; 
		}
		pMy_string->data[pMy_string->size] = c;
		pMy_string->size += 1;
		c = fgetc(fp);
	}
	if (c != EOF)
	{
		ungetc(c, fp);
	}
	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp) {
  	My_string* pMy_string = hMy_string;
	int i;
	for (i = 0; i <=   pMy_string->size; ++i) {
		fputc(pMy_string->data[i], fp);
	}
	return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item) {
  	int i;
  	char* pTemp;
  	My_string* pMy_string = hMy_string;

  	if (pMy_string->size == (pMy_string->capacity - 1)) {
   		pTemp = (char*) malloc((pMy_string->capacity * 2) * sizeof(char));
    	if (pTemp == NULL) {
      return FAILURE;
    }
    for (i = 0; i <= pMy_string->size; ++i) {
      pTemp[i] = pMy_string->data[i];
    }
    free(pMy_string->data);
    pMy_string->data = pTemp;
    pMy_string->capacity *= 2;
  	}

  	pMy_string->data[pMy_string->size] = item;
  	pMy_string->size += 1;

  	return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string) {
  My_string* pMy_string = hMy_string;

 	if(pMy_string == 0)
    {
      	return FAILURE;
    }
  
  	pMy_string->size--;
  	return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index) {
  	My_string* pMy_string = hMy_string;
  	if(index>pMy_string->size||index<0)
    	return NULL;
  	else
    {
      	return &(pMy_string->data[index]);
    }
}

char* my_string_c_str(MY_STRING hMy_string) {
  My_string* pMy_string = hMy_string;
  pMy_string->data[pMy_string->size] = '\0';
  return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend) {
  int i;
  char* pTemp = NULL;
  My_string* pResult = (My_string*) hResult;
  My_string* pAppend = (My_string*) hAppend;

  if (pResult->capacity <= pAppend->size + pResult->size) {
    pTemp = malloc(sizeof(char) * (pResult->capacity + pAppend->size));

    if (pTemp == NULL) {
      return FAILURE;
    }
    for (i = 0; i <= pResult->size; ++i) {
      pTemp[i] = pResult->data[i];
    }
    pResult->capacity += pAppend->size;
    free(pResult->data);
    pResult->data = pTemp;
  }

  for(i = 0; i <= pAppend->size; ++i) {
    pResult->data[i + pResult->size] = pAppend->data[i];
  }
  pResult->size += pAppend->size;
  return SUCCESS;
}

Boolean my_string_empty(MY_STRING hMy_string) {
  	My_string* pMy_string = hMy_string;
  	if(pMy_string->size > 0)
    {
      	return FALSE;
    }
  	return TRUE;
}

void my_string_destroy(Item* phMy_string) {
    My_string* pMy_string = (My_string*)*phMy_string;
    free(pMy_string->data);
    free(pMy_string);
    *phMy_string = NULL;
    return;
}

Status my_string_assignment(Item* pLeft, Item Right) {
  	My_string* pMy_string_left = NULL;
  	My_string* pMy_string_right = Right;
  	int i;
  	char* pTemp;
  	if (*pLeft == NULL) {
    	pMy_string_left = (My_string*) malloc(sizeof(My_string));
    	pTemp = (char*) malloc(sizeof(char)* (pMy_string_right->capacity));
    	if (pTemp == NULL) {
    		printf("Fail to allocate memory!\n");
        	return FAILURE;
      	}
   		if (pMy_string_left != NULL && pTemp != NULL) {
      		pMy_string_left->size = pMy_string_right->size;
      		pMy_string_left->capacity = pMy_string_right->capacity;
      		for (i = 0; i < pMy_string_right->size; i++) {
        		pTemp[i] = pMy_string_right->data[i];
      		}
      		pMy_string_left->data = pTemp;
      		*pLeft = pMy_string_left;
    	}
    	else {
      		if (pMy_string_left != NULL) {
        		free(pMy_string_left);
        		pLeft = NULL;
			return FAILURE;
      		}
      		if (pTemp != NULL) {
        		free(pTemp);
        		pLeft = NULL;
			return FAILURE;
      		}
    	}
  	}
  	else {
    pMy_string_left = *pLeft;
    if (pMy_string_left->capacity <= pMy_string_right->size) {
      	pTemp = (char*) malloc(sizeof(char)* (pMy_string_right->capacity));
      	if (pTemp == NULL) {
      		printf("Fail to allocate memory!\n");
        	return FAILURE;
      	}
      	free(pMy_string_left->data);
      	pMy_string_left->data = pTemp;
      	pMy_string_left->capacity = pMy_string_right->capacity;
    }
    pMy_string_left->size = pMy_string_right->size;
    for (i = 0; i < pMy_string_right->size; i++) {
      	pMy_string_left->data[i] = pMy_string_right->data[i];
    }
    *pLeft = pMy_string_left;
  }
	return SUCCESS;
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess) {
  	MY_STRING tempKey = NULL;
  	Status status;
  	char familyChar;
  	char wordChar;
  	tempKey = my_string_init_default();
  	if (tempKey == NULL) {
    	return FAILURE;
  	}
  	int i;
  	guess = tolower(guess);
  	for (i = 0; i < my_string_get_size(word); ++i) {
    	familyChar = tolower(*(my_string_at(current_word_family, i)));
    	wordChar = tolower(*(my_string_at(word, i)));

    	if (guess == wordChar) {
      		if (my_string_push_back(tempKey, guess) == FAILURE) {
        		return FAILURE;
      		}
   	 	}
    	else {
      		if (my_string_push_back(tempKey, familyChar) == FAILURE) {
        		return FAILURE;
      		}
    	}
  	}
  	status = my_string_assignment(&new_key, tempKey);
  	my_string_destroy(&tempKey);
  	return status;
}

Status my_string_print(MY_STRING hString){
    if (hString == NULL) {
        return FAILURE;
    }
    int i;
    for (i = 0; i < my_string_get_size(hString); i++) {
        printf("%c ",my_string_c_str(hString)[i]);
    }
    
    printf("\n");
    return SUCCESS;
}

Status my_string_print_matched_char(MY_STRING hString,char c){
    if (!hString) {
        printf("String is empty!!!\n");
        return FAILURE;
    }
    int i;
    int counter = 0;
    for (i = 0; i < my_string_get_size(hString); i++) {
        if (my_string_c_str(hString)[i] == c) {
            counter++;
        }
    }
    if (!counter) {
        printf("Sorry, there is no %c\n",c);
    }
    else{
        printf("Nice!There are %d %c(s) \n",counter,c);
    }
    return SUCCESS;
}
