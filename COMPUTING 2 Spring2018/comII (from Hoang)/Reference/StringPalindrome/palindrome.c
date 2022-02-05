//
//  palinedrome.c
//  Daily8
//
//  Created by Viet Tran Quoc Hoang on 3/28/16.
//  Copyright © 2016 Viet Tran Quoc Hoang. All rights reserved.
//

#include "palindrome.h"
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
        int ch = 0;
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
        return temp;
    }
    else{
        printf("Alloc memory of temp failed\n");
        return NULL;
    }
    
}

Status string_resize(String_Ptr hString){//avoid code duplication
    if (hString == NULL) {
        return FAILURE;
    }
    //printf("temp is created,size =%d\n",new_size);
    hString->capacity *=2;//double capacity
    char* temp = string_make_temp(hString, hString->size);
    if(temp!= NULL){
        free(hString ->char_array);
        hString->char_array= temp;
        
        return SUCCESS;
    }
    else{
        return FAILURE;
    }
    
}


Status get_line(String_Ptr hString, FILE * fp){
    if (hString == NULL || fp == NULL) {
        return FAILURE;
    }
    else{
        char c;
        while(fscanf(fp,"%c", &c)!=EOF) {//receives the entire strings,including all white spaces
            if(c == '\n'){
                break;//stop once a few chars have been recorded and receive another white space
            }
            else{
                //only accept char, skip any white space
                hString->char_array[hString->size]=c;
                hString->size++;
                if(hString->size == hString->capacity){//if size of string > capacity, create new char_array to store
                    if(string_resize(hString) == FAILURE){
                        return  FAILURE;
                    }
                }
            }
        }
        if (hString->size == 0){
            //printf("end of file,stopping programme \n");
            return FAILURE;
        }
        else{
            return SUCCESS;
        }
        
    }
}

int is_palindrome(String_Ptr hString){
    if (hString == NULL) {
        return 0;
    }
    int i = 0;
    int length = 0;
    char temp[hString->size];
    for (i = 0; i < hString->size; i++) {
        if (isalpha(hString->char_array[i])) {
            temp[length] = toupper(hString->char_array[i]);
            length++;
        }
    }
    //    printf("Content inside temp:");
    //    int j;
    //    for ( j = 0; j < length; j++) {
    //        printf("%c",temp[j]);
    //    }
    //    printf("\n");
    hString->size = 0;
    int tail = length-1;//last char is empty becos of post increment
    int head = 0;
    for (head = 0; head < length/2; head++,tail--) {
        if (temp[head] != temp[tail]) {
            //printf("head char = %c and head index= %d\n",temp[head],head);
            //printf("tail char = %c and tail index= %d\n",temp[tail],tail);
            
            return 0;
        }
    }
    return 1;
}

void reset_size(String_Ptr hString){
    hString->size = 0;
}


