#include <stdio.h>
#include <stdlib.h>

#include "my_string.h"


typedef struct my_string_private
{
    //PUBLIC STUFF
    int (*get_capacity)(MY_STRING hMy_string);
    int (*get_size)(MY_STRING hMy_string);
    void (*destroy)(MY_STRING* phMy_string);
    Status (*push_back)(MY_STRING hMy_string, char item);
    Status (*pop_back)(MY_STRING hMy_string);
    char* (*at)(MY_STRING hMy_string, int index);
    Status (*extraction)(MY_STRING hMy_string, FILE* fp);
    char* (*c_str)(MY_STRING hMy_string);
    int (*string_compare)(MY_STRING hMy_String1, MY_STRING hMy_string2);
    Status (*concat)(MY_STRING hMy_string_destination, MY_STRING hMy_string_addition);
    void(*item_destroy)(Item_ptr* item_handle);
    Status(*item_assign)(Item_ptr* item_handle, Item_ptr item);
    Status(*get_line)(MY_STRING hMy_string, FILE* fp);

    //PRIVATE STUFF
    int size;
    int capacity;
    char* data;
} My_string;

int my_string_get_capacity(MY_STRING);
int my_string_get_size(MY_STRING);
int string_compare(MY_STRING, MY_STRING);

char* my_string_at(MY_STRING, int);
char* c_str(MY_STRING);


Status my_string_pop_back(MY_STRING);
Status my_string_push_back(MY_STRING, char);
Status my_string_extraction(MY_STRING, FILE*);
Status my_string_concat(MY_STRING, MY_STRING);
Status get_line(MY_STRING hMy_string, FILE* fp);
Status my_string_display(MY_STRING hString, FILE* out);

void item_destroy(Item_ptr* item_handle);
Status item_assign(Item_ptr* item_handle, Item_ptr item);
Status my_string_display(MY_STRING hString, FILE* out);

void my_string_destroy(MY_STRING*);


MY_STRING my_string_init_default()
{
    My_string* pString = NULL;

    pString = (My_string*)malloc(sizeof(My_string));

    if (pString != NULL)
    {
        //void* functions
        pString->destroy = my_string_destroy;
        pString->at = my_string_at;
        pString->pop_back = my_string_pop_back;
        pString->push_back = my_string_push_back;
        pString->extraction = my_string_extraction;
        pString->get_size = my_string_get_size;
        pString->get_capacity = my_string_get_capacity;
        pString->c_str = c_str;
        pString->string_compare = string_compare;
        pString->concat = my_string_concat;
        pString->item_destroy = item_destroy;
        pString->item_assign = item_assign;
        pString->get_line = get_line;


        pString->size = 0;
        pString->capacity = 8;
        pString->data = (char*)malloc(sizeof(char) * pString->capacity);

        if (pString->data == NULL)
        {
            free(pString);
            pString = NULL;
        }
    }

    return (MY_STRING)pString;
}

void my_string_destroy(MY_STRING* phMy_string)
{
    My_string* temp = (My_string*) *phMy_string;

    if (temp != NULL)
    {
        if (temp->data != NULL)
        {
            free(temp->data);
            free(temp);
        }
    }

    *phMy_string = NULL;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
    My_string* pString = (My_string*)hMy_string;

    if (pString != NULL && index < pString->size && index >= 0)
        return &(pString->data[index]);

    return NULL;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;

    if (pString->size <= 0) return FAILURE;
    
    pString->size--;
    return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
    int i;
    My_string* pString = (My_string*)hMy_string;
    Status status = FAILURE;

    if (pString != NULL)
    {
        if (pString->size >= pString->capacity)
        {
            char *temp;
            pString->capacity *= 2;
            temp = (char*)malloc(sizeof(char) * pString->capacity);

            if (temp == NULL)
            {
                pString->capacity /= 2;
                return FAILURE;
            }

            for (i = 0; i < pString->size; i++)
            {
                temp[i] = pString->data[i];
            }

            free(pString->data);
            pString->data = temp;
        }

        pString->data[pString->size] = item;
        pString->size++;

        status = SUCCESS;
    }

    return status;
}

int string_compare(MY_STRING hMy_string1, MY_STRING hMy_string2)
{
    My_string* pString1 = (My_string*)hMy_string1;
    My_string* pString2 = (My_string*)hMy_string2;

    int i = 0;
    int retVal = 0;
    int maxSize = (pString1->size > pString2->size) ? pString1->size : pString2->size;

    while (i < maxSize)
    {
        if (i > pString2->size) return 1;
        if (i > pString1->size) return -1;

        if (pString1->data[i] < pString2->data[i]) retVal = -1;
        else if (pString1->data[i] > pString2->data[i]) retVal = 1;

        if (retVal != 0) break;

        i++;
    }

    return retVal;
}

Status my_string_concat(MY_STRING hMy_string_destination, MY_STRING hMy_string_addition)
{
    My_string* pStringDest = (My_string*)hMy_string_destination;
    My_string* pStringAdd = (My_string*)hMy_string_addition;

    int i = 0;
    int combinedSize = pStringDest->size + pStringAdd->size;

    pStringDest->data = (char*)realloc(pStringDest->data, sizeof(char) * combinedSize);

    if (pStringDest == NULL || pStringAdd == NULL) return FAILURE;

    for (i = 0; i < pStringAdd->data[i]; i++)
        pStringDest->push_back((MY_STRING)pStringDest, pStringAdd->data[i]);

    return SUCCESS;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
    My_string* pString = (My_string*)hMy_string;

    const int space = 32;
    const int newline = 10;
    int conversions;
    char character;

    if (pString == NULL) return FAILURE;

    pString->size = 0;

    // remove leading space(s)
    fscanf(fp, " ");
    conversions = fscanf(fp, "%c", &character);

    while (conversions > 0 && character != space && character != newline)
    {
        pString->push_back((MY_STRING)pString, character);
        conversions = fscanf(fp, "%c", &character);      
    }

    if (conversions != 1 && conversions != EOF) return FAILURE;

    return SUCCESS;
}

int my_string_get_size(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;   
    int size = -1;

    if (pString != NULL) size = pString->size;

    return size;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;
    int capacity = -1;

    if (pString != NULL) capacity = pString->capacity;

    return capacity;
}

char* c_str(MY_STRING hMy_string)
{
    My_string* pString = (My_string*)hMy_string;
    char* temp;
    int i;

    if (pString->capacity <= pString->size) // Not even big enough for NULL terminator so resize
    {
        pString->capacity *= 2;
        temp = (char*)malloc(sizeof(char) * pString->capacity);

        if (temp == NULL)
        {
            pString->capacity /= 2;
            return NULL;
        }

        for (i = 0; i < pString->size; i++)
        {
            temp[i] = pString->data[i];
        }

        free(pString->data);
        pString->data = temp;
    }

    //Simply make sure the string has a NULL terminator before showing it as a c-string.
    pString->data[pString->size] = '\0';

    return pString->data;
}

MY_STRING my_string_init_c_str(const char* c_string)
{
    int i = 0;
    int index = 0;
    int capacity = 8;

    My_string* pString = NULL;
    pString = (My_string*)malloc(sizeof(My_string));

    while (c_string[index] != '\0')
        index++;
    
    for (i = 1; index > capacity; i++)
        capacity *= i;

    if (pString != NULL)
    {
        //void* functions
        pString->destroy = my_string_destroy;
        pString->at = my_string_at;
        pString->pop_back = my_string_pop_back;
        pString->push_back = my_string_push_back;
        pString->extraction = my_string_extraction;
        pString->get_size = my_string_get_size;
        pString->get_capacity = my_string_get_capacity;
        pString->c_str = c_str;
        pString->string_compare = string_compare;
        pString->concat = my_string_concat;
        pString->item_destroy = item_destroy;
        pString->item_assign = item_assign;

        pString->size = index;
        pString->capacity = capacity;
        pString->data = (char*)malloc(sizeof(char) * pString->capacity);

        if (pString->data == NULL)
        {
            free(pString);
            pString = NULL;
        }

        for (i = 0; i<index; i++)
        {
            pString->data[i] = c_string[i];
        }
    }

    return (MY_STRING)pString;
}

Status item_assign(Item_ptr* left, Item_ptr right)
{
    int i;
    My_string* pLeft = (My_string*)*left;
    My_string* pRight = (My_string*)right;

    //if (pLeft == NULL) pLeft = my_string_init_default();
    if (pLeft == NULL) pLeft = (My_string*)my_string_init_default();
    if (pLeft == NULL) return FAILURE;
    if (pRight == NULL) return FAILURE;

    if (pLeft->get_capacity((MY_STRING)pLeft) < pRight->size) //make sure we have room
    {
        free(pLeft->data);
        pLeft->capacity = pRight->size;
        pLeft->data = (char*)malloc(sizeof(char) * pLeft->capacity);
    }

    pLeft->size = pRight->size;  //adjust size

    for (i = 0; i < pLeft->size; i++) //copy data
        pLeft->data[i] = pRight->data[i];
        
    *left = pLeft;

    return SUCCESS;
}

void item_destroy(Item_ptr* item_handle)
{
    My_string* temp = (My_string*)*item_handle;

    if (temp != NULL)
    {
        free(temp->data);
        free(temp);
    }

    *item_handle = NULL;
}

Status get_line(MY_STRING hMy_string, FILE* fp)
{
    My_string* pString = (My_string*)hMy_string;

    const int newline = 10;
    int conversions;
    char character;

    pString->size = 0;

    if (pString == NULL) return FAILURE;

    conversions = fscanf(fp, "%c", &character);

    while (conversions > 0 && character != newline)
    {
        pString->push_back((MY_STRING)pString, character);
        conversions = fscanf(fp, "%c", &character);
    }

    if (conversions != 1 && conversions != EOF) return FAILURE;
    if (pString->size == 0) return FAILURE;


    return SUCCESS;
}