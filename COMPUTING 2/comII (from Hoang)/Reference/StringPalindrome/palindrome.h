//
//  palinedrome.h
//  Daily8
//
//  Created by Viet Tran Quoc Hoang on 3/28/16.
//  Copyright © 2016 Viet Tran Quoc Hoang. All rights reserved.
//

#ifndef palinedrome_h
#define palinedrome_h
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "status.h"
typedef struct string* String_Ptr;
String_Ptr string_init_default();
void string_destroy(String_Ptr* phString);
Status string_insertion(String_Ptr hString, FILE * fp);
void* string_make_temp(String_Ptr hString,unsigned int old_size);
Status string_resize(String_Ptr hString);
//Precondition: hString is a handle to a string object, fp is a pointer
// to a file to read a string from
//Postcondition: SUCCESS if we successfully read a single string from the file,
// FAILURE if reached the EOF and string is still size zero
//***get first line from file
Status get_line(String_Ptr hString, FILE * fp);

//Precondition: hString is a handle to a string object
//Postcondition: return 1 if string inside is palindrome and 0 if not
int is_palindrome(String_Ptr hString);
void reset_size(String_Ptr hString);
#endif /* palinedrome_h */
