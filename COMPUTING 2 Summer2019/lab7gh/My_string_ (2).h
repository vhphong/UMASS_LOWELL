#ifndef MY_STRING_H
#define MY_STRING_H

#include "Common.h"

struct my_string_public;

typedef struct my_string_public* MY_STRING;

struct my_string_public
{
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
};


MY_STRING my_string_init_default(void);
MY_STRING my_string_init_c_str(const char*);



void my_string_destroy(MY_STRING*);

#endif