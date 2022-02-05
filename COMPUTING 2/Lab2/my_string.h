#include <stdlib.h>

typedef void* MY_STRING;

/*
 Precondition: None
 Postcondition: Allocate space for a string object that represents the empty
 string. The  string will have capacity 7 and size 0 by default. A copy of The
 address of the opaque object will be returned on success and NULL on failure
*/
MY_STRING my_string_init_default(void);

/*
 Precondition: c_string is a valid null terminated c_string
 Postcondition: Allocate space for a string object that  represents a string
 with the same value as the giver c-string. The capacity of the string object
 will be set to one greater than is required to hold the string. A copy of the
 address of the object will be returned upon success, and NULL on failure.
*/
MY_STRING my_string_init_c_string(const char* c_string);

/*
 Precondition: hMy_string is the handle to a valid My_string object
 Postcondition: Returns a copy of the integer value of the object's capacity
*/
int my_string_get_capacity(MY_STRING hMy_string);

/*
 Precondition: hMy_string is the handle to a valid My_string object
 Postcondition: Returns a copy of the integer value of the object's size
*/
int my_string_get_size(MY_STRING hMy_string);

/*
 Precondition: hLeft_string and hRight_string are valid My_string objects.
 Postcondition: returns an integer less than 0 if the string represented by
 hLeft_string is lexicographically smaller than hRight_string. If one string is
 a prefix of the other string then the shorter string is considered to be the
 smaller one. (app is less than apple). Returns 0 if the strings are the same
 and an integer greater than 0 if hLeft_string is greater than hRight_string;
*/
int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string);

/*
 Precondition: phMy_string holds the address  of a handle to a MY_STRING object
 Postcondition: The memory used for the MY_STRING object has been reclaimed by
 the system and the handle referred to by the pointer phMy_string has been set
 to null
*/
void my_string_destroy(MY_STRING* phMy_string);