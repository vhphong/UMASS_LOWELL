#include "string.h"
struct string{
    char* char_array;
    int capacity;
    int size;
};
typedef struct string String;

String_Ptr string_init_default(){
    String_Ptr string_struct = (String_Ptr)malloc(sizeof(String));
    if(string_struct){
        string_struct->capacity = 10;
        string_struct->char_array =(char*)malloc(sizeof(char)*(string_struct->capacity));
        string_struct->size = 0;
        if(string_struct->char_array){
            return string_struct;
        }
        else{
            free(string_struct);
            string_struct = NULL;
            printf("Alloc memory of string_struct->char_array failed.\n");
            return NULL;
        }
    }
    else{
        printf("Alloc memory of string_struct failed.\n");
        return NULL;
    }
}

String_Ptr string_init_c_string(char* c_str){
    int i;
    int len =0;
    String_Ptr string_struct = (String_Ptr)malloc(sizeof(String));
    if(string_struct==NULL){
        printf("Alloc memory of string_struct failed.\n");
        free(string_struct);
        string_struct = NULL;
        return NULL;
    }
    while(c_str[len] != '\0'){
        len++;
    }
    if (len == 0){
        printf("string is NULL(len = 0)\n");
        free(string_struct);
        string_struct = NULL;
        return NULL;
    }
    string_struct->capacity = len+1;
    string_struct->size = len;
    
    string_struct->char_array =(char*)malloc(sizeof(char) * string_struct->capacity );
    if(string_struct->char_array){
        for(i = 0; i< string_struct->size; i++){
            string_struct->char_array[i]= c_str[i];
        }
        return (String_Ptr)string_struct;
    }
    else{
        free(string_struct);
        string_struct = NULL;
        printf("Alloc memory of string_struct->char_array failed.\n");
        return NULL;
    }
    
    
}

void string_destroy(String_Ptr* phString){
    String_Ptr string_struct = (String_Ptr) *phString;
    if (string_struct->char_array != NULL) {
            free(string_struct->char_array);
        }
    if(string_struct!= NULL){
        free(string_struct);
    }
    *phString = NULL;
    return;
}

int string_get_capacity(String_Ptr hString){
    if (hString == NULL) {
        return -1234;
    }
    return hString->capacity;
}

int string_compare(String_Ptr string1, String_Ptr string2){
    if (string1 == NULL|| string2 == NULL) {
        printf("string_compare fails because it cannot compare NULL\n");
        return 0;
    }
    int i=0;
    if((string1->size) != (string2->size)){//different sizes
        return string1->size - string2->size;
    }
    else{//equal length case
        for( i = 0; i < string1->size ; i++){//loop through entire string,either string is fine
            if ((string1->char_array[i]) != (string2->char_array[i])){//compare char by char
                return (string1->char_array[i]) - (string2->char_array[i]);
            }
        }
        
    }
    return 0;
}

int string_get_size( String_Ptr pString){
    return pString->size;
}

Status string_extraction(String_Ptr hString, FILE * fp){
    if (hString == NULL) {
        return FAILURE;
    }
    if( fp == NULL){
        printf("Invalid file name,make sure name of txt file matches fopen command\n");
        exit(1);//Have to CRASH otherwise will produce null values on everything.
    }
    else{
        char c;
        hString->size = 0;
        while(fscanf(fp,"%c", &c)!=EOF) {//receives the entire strings,including all white spaces
            if(hString->size!=0 && isspace(c)){
                //ungetc(c,fp);
                break;//stop once a few chars have been recorded and receive another white space
            }
            else{
                if(!isspace(c)){//only accept char, skip any white space
                    hString->char_array[hString->size]=c;//i = hString->size
                    hString->size++;//++i = hString->size;
                    if(hString->size == hString->capacity){//if size of string > capacity, create new char_array to store
                        if(string_resize(hString) == FAILURE){
                            return  FAILURE;
                        }
                    }
                }
            }
        }
        if (hString->size == 0){
            return FAILURE;//printf("end of file,stopping programme \n");
        }
        else{
            return SUCCESS;
        }
    }
}


Status string_insertion(String_Ptr hString, FILE * fp){
    if (hString == NULL) {
        return FAILURE;
    }
    if( fp == NULL){
        printf("Invalid file name\n");
        return FAILURE;
    }
    else{
        int i = 0;
        int ch;
        for ( i = 0; i < (hString->size); i++){
            ch = (hString->char_array[i]);
            if(fputc(ch, fp)==EOF)//if empty string
            {printf("Error writing file\n");
                return FAILURE;
            }
            else
                continue;
        }
        return SUCCESS;
    }
}

void* string_make_temp(String_Ptr hString,unsigned int old_size){
    if (hString == NULL) {
        return NULL;
    }
    char* temp =(char*)malloc((sizeof(char)*(hString->capacity)));
    //printf("Size exceeds capacity,newly generated capacity = %d\n",hString->capacity);
    int j;
    if(temp){
        for (j = 0; j < old_size; j++) {
            temp[j]= hString->char_array[j];//copy char_array into temp
        }
    }
    else{
        printf("Alloc memory of temp failed\n");
        return NULL;
    }
    return temp;
}

Status string_resize(String_Ptr hString){//avoid code duplication
    if (hString == NULL) {
        return FAILURE;
    }
    //printf("temp is created,size =%d\n",new_size);
    hString->capacity *=2;//double capacity
    char* temp = string_make_temp(hString, hString->size);
    if(temp){
        free(hString ->char_array);
        hString->char_array= temp;
        
        return SUCCESS;
    }
    else{
        return FAILURE;
    }
    
}

Status string_push_back(String_Ptr hString, char item){
    if (hString == NULL) {
        return FAILURE;
    }
    hString->char_array[hString->size]=item;
    (hString->size)++;
    if(hString->size==hString->capacity){
        if(string_resize(hString) == FAILURE){
            return  FAILURE;
        }
    }
    return SUCCESS;
}



char* string_c_str(String_Ptr hString){
    if (hString == NULL) {
        return NULL;
    }
    hString->char_array[hString->size] = '\0';
    return hString->char_array;
}

Boolean string_empty(String_Ptr hString){
    return (Boolean)(hString->size == 0);
}

Status string_concat(String_Ptr hResult, String_Ptr hAppend){
    if (hResult == NULL || hAppend == NULL) {
        return FAILURE;
    }
    int i;
    for (i = 0; i < hAppend->size; i++) {
        hResult->char_array[hResult->size] = hAppend->char_array[i];
        hResult->size++;
        if (hResult->size == hResult->capacity) {
            if(string_resize(hResult) == FAILURE){
                return  FAILURE;
            }
        }
    }
    return  SUCCESS;
}

Status string_print(String_Ptr hString){//print all char inside string ptr
    if (hString == NULL) {
        return FAILURE;
    }
    int i;
    for (i = 0; i < string_get_size(hString); i++) {
        printf("%c ",string_c_str(hString)[i]);
    }
    
    printf("\n");
    return SUCCESS;
}

Status string_print_matched_char(String_Ptr hString,char c){
    if (!hString) {
        printf("string ptr is empty,cant print\n");
        return FAILURE;
    }
    int i;
    int counter = 0;
    for (i = 0; i < string_get_size(hString); i++) {//compare char by char
        if (string_c_str(hString)[i] == c) {
            counter++;//+1 each time there is a match
        }
    }
    if (!counter) {
        printf("I'm sorry,there is no %c\n",c);
    }
    else if(counter == 1){
        printf("Nice!There is 1 %c \n",c);//prompt user
    }
    else{
        printf("Nice!There are %d %c(s) \n",counter,c);//prompt user
    }
    return SUCCESS;
}

//Precondition:current_word_family, new_key and word are all handles to valid
// MY_STRING opaque objects. guess is an alphabetical character that can be either
// upper or lower case.
//Postcondition: Returns SUCCESS after replacing the string in new_key with the key
// value formed by considering the current word family, the word and the guess.
// Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(String_Ptr current_word_family, String_Ptr new_key, String_Ptr word, char guess){
    int i;
    if ( string_empty(current_word_family)  || string_empty(word) || !guess|| !new_key ) {
        printf("one of the string ptr object is invalid\n");
        return FAILURE;
    }
    if (string_get_size(word) != string_get_size(current_word_family)) {
        printf("word family has to be the same length as the dictionary word\n");
        return FAILURE;
    }
    new_key->size = 0;
    for (i = 0; i < string_get_size(word); i++) {
        if (tolower(guess) == tolower(string_c_str(word)[i])) {
            if(string_push_back(new_key, tolower(guess)) == FAILURE){
                return FAILURE;
            }
        }
        else{// if( string_c_str(current_word_family)[i] != '-'){
            if(string_push_back(new_key, string_c_str(current_word_family)[i]) == FAILURE){
                return FAILURE;
            }
        }
        //else{
        //    if(string_push_back(new_key, '-') == FAILURE){
        //        return FAILURE;
        //   }
        //}
    }
    return SUCCESS;
}