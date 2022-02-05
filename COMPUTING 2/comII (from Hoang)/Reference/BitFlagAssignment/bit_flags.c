/***********************************************************
 Author: Viet Tran Quoc Hoang
 Date: 2/13/2016
 Effort: 12 hours
 Purpose: A bitmap array implementation using opaque object. Can be used to remove duplicate efficiently
 Interface proposal: 
 A function that try to detect the biggest size needed before object is created.(Given a set of datas,find max value amongst all datas/find max value of a char in a set of chars/find max size of many structs)
 ***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "bit_flags.h"

struct bitArray{
    unsigned int* flag_holder;
    int size;
    int capacity;
};

typedef struct bitArray bit;

void bit_flags_display(BIT_FLAGS hBit_flags,unsigned int size);

Status bit_flags_resize(BIT_FLAGS hBit_flags, unsigned int new_size);

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits){
    if (number_of_bits<0){
        printf("Negative value not allowed\n");
        return NULL;
    }
    bit* bit_struct = (bit*)malloc(sizeof(bit));
    if(bit_struct){
        bit_struct->size = number_of_bits;
        bit_struct->capacity = (bit_struct->size)+1;
        bit_struct->flag_holder = (unsigned int*)malloc(sizeof(unsigned int)*1);
        if(bit_struct->flag_holder){
            bit_struct->flag_holder[0] = 0;
            return (BIT_FLAGS)bit_struct;
        }
        else{
            free(bit_struct);
            bit_struct = NULL;
            printf("Alloc memory of string_struct->flag_holder failed\n");
            return NULL;
        }
    }
    else{
        printf("Alloc memory of string_struct failed\n");
        return NULL;
    }
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position<0) {
        printf("Negative value not allowed\n");
        return FAILURE;
    }
    bit* bit_struct = (bit*)hBit_flags;
    if(bit_struct==NULL){
        printf("Invalid object\n");
        return FAILURE;
    }
    //printf("Turning bits %d on\n",flag_position);
    if (flag_position > bit_struct->capacity){//needed resize
        if(bit_flags_resize(hBit_flags, flag_position)==FAILURE){
            return FAILURE;
        }
    }
    int index = flag_position/32;
    int mask = flag_position%32;
    (bit_struct->flag_holder[index]) |= 1 << (mask);//set bits on
    return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position<0) {
        printf("Negative value not allowed\n");
        return FAILURE;
    }
    bit* bit_struct = (bit*)hBit_flags;
    if(bit_struct==NULL){
        printf("Invalid object\n");
        return FAILURE;
    }
    //printf("Turning bits %d off\n",flag_position);
    if (flag_position > bit_struct->capacity){//needed resize
        if(bit_flags_resize(hBit_flags, flag_position)==FAILURE){
            return FAILURE;
        }
    }
    int index = flag_position/32;
    int mask = flag_position%32;
    (bit_struct->flag_holder[index]) &= ~(1 << (mask));//set bits off
    return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position < 0) {
        printf("Negative bit error\n");
        return -1;
    }
    bit* bit_struct = (bit*)hBit_flags;
    if(bit_struct==NULL){
        printf("Invalid object\n");
        return -1;
    }
    int index = flag_position/32;
    int mask = flag_position%32;
    if (flag_position > bit_struct->capacity){
        return -1;//out of bound error
    }
    else if( ((bit_struct->flag_holder[index]) &(1 <<mask))==0){//if bit is off
        return 0;
    }
    else
        return 1; //if bit is on
}

int bit_flags_get_size(BIT_FLAGS hBit_flags){
    bit* bit_struct = (bit*)hBit_flags;
    if(bit_struct){
    return bit_struct->size;
    }
    else{
        printf("Invalid object\n");
        return -1;
    }
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags){
    bit* bit_struct = (bit*)hBit_flags;
    if(bit_struct){
    return bit_struct->capacity;
    }
    else{
        printf("Invalid object\n");
        return -1;
    }
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags){
    bit* bit_struct = (bit*)*phBit_flags;
    if(bit_struct!=NULL){
        free(bit_struct->flag_holder);
        free(bit_struct);
    }
    *phBit_flags = NULL;
    return;
}

void bit_flags_display(BIT_FLAGS hBit_flags,unsigned int size){
    int i;
    for (i=0;i<=size;i++){
        printf("%d",bit_flags_check_flag(hBit_flags,i));
        if(i%4==3){
            printf(" ");
        }
    }
    printf("\n");
    return;
}

Status bit_flags_resize(BIT_FLAGS hBit_flags,unsigned int new_size){//avoid code duplication in set_flag and unset_flag
    bit* bit_struct = (bit*)hBit_flags;
    //printf("temp is created,size =%d\n",new_size);
    unsigned int* temp = (unsigned int*)malloc(sizeof(unsigned int)*1);
    if(temp){
        temp[0] = 0;
        int i;
        for ( i=0; i <= (bit_struct->capacity); i++){//check flag to see if bit is on in struct_bit
            if(bit_flags_check_flag(hBit_flags,i)== 1){
                (temp[i/32]) |= 1 << (i%32);//then turn bits on in temp too
            }
        }
        free(bit_struct->flag_holder);
        bit_struct->flag_holder= temp;
        bit_struct->capacity = new_size+1;
        bit_struct->size = new_size;
        return SUCCESS;
    }
    else{
        return FAILURE;
    }
    
}

