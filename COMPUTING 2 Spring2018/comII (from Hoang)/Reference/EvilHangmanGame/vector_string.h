

#ifndef vector_string_h
#define vector_string_h

#include "status.h" 
#include "string.h"
typedef struct vector_string * Vector_String_Ptr;

// Precondition: None
// Postcondition: allocates memory to a pointer to a vector of strings // it also sets the size to 0 and the capacity to 0
// it allocates an array of string_ptr of capacity 1
Vector_String_Ptr vector_string_init_default(void);

// Precondition: phVectorString: a pointer to a handle to a vector of strings // Postcondition: makes sure that the memory is correctly freed
// You have multiple levels to free accordingly:
// 1- you need to loop through the array of String_Ptr and
// call the strong_destroy function
// 2- You need to free the array itself
// 3- You need to free the vector of strings (*phVectorString)
void vector_string_destroy(Vector_String_Ptr * phVectorString);

// Precondition: hVectorString: a handle to a vector of strings and
// hString: a handle to the string to be added. The string is already
// created and allocated by the calling program. Check if the hString
// is NULL before adding it to the vector.
// Postcondition: Adding a handle to a string to the end of the vector.
// If size == capacity of the vector (i.e, no room to add the string), then
// the vector needs to expand to hold more strings.
// Returns SUCCESS of the string was successfully added.
// Return FAILURE:
// - hString was NULL or the hVectorString was NULL.
// - Could not expand the internal array
Status vector_string_push_back(Vector_String_Ptr hVectorString, String_Ptr hString);

// Precondition: hVectorString: a handle to a vector of strings to get its size
// Postcondition: the size of the vector of strings.
int vector_string_get_size(Vector_String_Ptr hVectorString);

// Preconiditon: hVectorString: a handle to a vector of strings to get its capacity
// Postcondition: the capacity of the vector of strings
int vector_string_get_capacity(Vector_String_Ptr hVectorString);

// Precondition: hVectorString: a handle to a vector of strings to check if// empty or not
// Postcondition: True if it is empty, false otherwise
Boolean vector_string_empty(Vector_String_Ptr hVectorString);

// Precondition: hVectorString: a handle to a vector of strings and the index of the // string to return
// Postcondition: a pointer to a string pointer. Returns null if the
// index is negative or > size.
String_Ptr* vector_string_at(Vector_String_Ptr hVectorString, int index);

void* vector_string_make_temp(Vector_String_Ptr hVectorString,unsigned int old_size);

Status vector_string_resize(Vector_String_Ptr hVectorString);

//load words from txt file to vector of string
void vector_string_load_one_word_of_size(unsigned int size, Vector_String_Ptr hVectorString);

Vector_String_Ptr load_dictionary_of_size(int size);
#endif /* vector_string_h */
