
#include "vector_string.h"
struct vector_string
{
    int size;
    int capacity;
    String_Ptr * data;
};
typedef struct vector_string Vector_String, * Vector_String_Ptr;

// Precondition: None
// Postcondition: allocates memory to a pointer to a vector of strings
// it also sets the size to 0 and the capacity to 0
// it allocates an array of string_ptr of capacity 1
Vector_String_Ptr vector_string_init_default(void){
    Vector_String_Ptr vector_struct = (Vector_String_Ptr)malloc(sizeof(Vector_String));
    if (vector_struct) {
        vector_struct->size = 0;
        vector_struct->capacity = 0;

        vector_struct->data = (String_Ptr*)malloc(sizeof(String_Ptr)*1);
        if (!vector_struct->data) {
            free(vector_struct);
            vector_struct = NULL ;
        }
        return (Vector_String_Ptr)vector_struct;
    }
    return NULL;
}

// Precondition: phVectorString: a pointer to a handle to a vector of strings
// Postcondition: makes sure that the memory is correctly freed
// You have multiple levels to free accordingly:
// 1- you need to loop through the array of String_Ptr and
// call the string_destroy function
// 2- You need to free the array itself
// 3- You need to free the vector of strings (*phVectorString)
void vector_string_destroy(Vector_String_Ptr *phVectorString){
    Vector_String_Ptr vector_struct = (Vector_String_Ptr)*phVectorString;
    if (vector_struct != NULL) {
        int i;
        for (i = 0; i < vector_struct->size; i++) {
            if (vector_struct->data[i] != NULL) {
                string_destroy(&vector_struct->data[i]);
            }
        }
        free(vector_struct->data);
        free(vector_struct);
    }
    *phVectorString = NULL;
    return;
}

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
Status vector_string_push_back(Vector_String_Ptr hVectorString, String_Ptr hString){
    if (hString == NULL || hVectorString == NULL) {
        return  FAILURE;
    }
    if(hVectorString->size == hVectorString->capacity){
        if(vector_string_resize(hVectorString) == FAILURE){
            return  FAILURE;
        }
    }
    hVectorString->data[hVectorString->size] = string_init_c_string(string_c_str(hString));
    (hVectorString->size)++;
    return SUCCESS;
}

// Precondition: hVectorString: a handle to a vector of strings to get its size
// Postcondition: the size of the vector of strings.
int vector_string_get_size(Vector_String_Ptr hVectorString){
    if (hVectorString == NULL) {
        return -1;
    }
    return hVectorString->size;
}

// Preconiditon: hVectorString: a handle to a vector of strings to get its capacity
// Postcondition: the capacity of the vector of strings
int vector_string_get_capacity(Vector_String_Ptr hVectorString){
    return hVectorString->capacity;
}

// Precondition: hVectorString: a handle to a vector of strings to check if// empty or not
// Postcondition: True if it is empty, false otherwise
Boolean vector_string_empty(Vector_String_Ptr hVectorString){
    return (Boolean)(hVectorString->size == 0);
}

Status vector_string_resize(Vector_String_Ptr hVectorString){
    if (hVectorString == NULL) {
        return  FAILURE;
    }
    if (hVectorString->capacity == 0) {
        hVectorString->capacity++;
    }
    (hVectorString->capacity) *= 2;
    String_Ptr* temp = (String_Ptr*)vector_string_make_temp(hVectorString, hVectorString->size);
    if (temp) {
        free(hVectorString->data);
        hVectorString->data = temp;
        return SUCCESS;
    }
    return FAILURE;
}

void* vector_string_make_temp(Vector_String_Ptr hVectorString,unsigned int old_size){
    String_Ptr* temp = (String_Ptr*)malloc(sizeof(String_Ptr)*hVectorString->capacity);
    if (temp) {
        int j;
        for ( j = 0; j < hVectorString->size; j++) {
            temp[j] = hVectorString->data[j];
        }
    }
        return (void*) temp;
}

// Precondition: hVectorString: a handle to a vector of strings and the index of the // string to return
// Postcondition: a pointer to a string pointer. Returns null if the
// index is negative or > size.
String_Ptr* vector_string_at(Vector_String_Ptr hVectorString, int index){
    if (hVectorString == NULL) {
        return NULL;
    }
    if ( index < 0 || index > hVectorString->size) {
        return NULL;
    }
    else {
        String_Ptr* pString = &(hVectorString->data[index]);
        return pString;
    }
}

//Load one word of given size to check for valid length;
void vector_string_load_one_word_of_size(unsigned int size, Vector_String_Ptr hVectorString){
    String_Ptr word = string_init_default();
    FILE* file = fopen("dictionary.txt", "r");
    while (string_extraction( word, file)) {
        if (string_get_size(word) == size) {
            vector_string_push_back(hVectorString, word);
            break;
        }
    }
    fclose(file);
    string_destroy(&word);
}

//Load ALL words at given length
Vector_String_Ptr load_dictionary_of_size(int size){
    Vector_String_Ptr dictionary = vector_string_init_default();
    String_Ptr word = string_init_default();
    FILE* fp = fopen("dictionary.txt","r");
    while (string_extraction(word, fp)) {
        if (string_get_size(word) == size) {
            vector_string_push_back(dictionary, word);
        }
    }
    string_destroy(&word);
    fclose(fp);
    return dictionary;
}

