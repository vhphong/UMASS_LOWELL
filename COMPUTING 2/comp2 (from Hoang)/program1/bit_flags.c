/*********************************************************** 
Author: Phong Vo
Date: 02/18/2018 
Effort: 20 hours 
Purpose: Combining previous assignments to make an opaque object wrapper
Interface proposal: The interface need a function that display the whole bits in the array.
			Another function that take an integer as a decimal number and turn on a series 
			of bits (set to 1) corresponding to that number and turn off (set to 0) the rest.	
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "bit_flags.h"

struct bitFlag{
    unsigned int* flag_holder;
    int size;
    int capacity;
};

typedef struct bitFlag bit;

void bit_flags_display(BIT_FLAGS hBit_flags, unsigned int size);

Status fixSize(BIT_FLAGS hBit_flags, unsigned int new_size);

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits){
	bit* bit_flag = (bit*)malloc(sizeof(bit));
    if (number_of_bits < 0){
        printf("Invalid value, positive number only!!\n");
        bit_flag = NULL;
        return bit_flag;
    }
    

    
    if(bit_flag){
        bit_flag -> size = number_of_bits;
        bit_flag -> capacity = (bit_flag -> size) + 1;
        bit_flag -> flag_holder = (unsigned int*)malloc(sizeof(unsigned int)*1);
        if(bit_flag -> flag_holder){
            bit_flag -> flag_holder[0] = 0;
            return bit_flag;
        }
        else{
            free(bit_flag);
            printf("Failed to allocate memory for bit_flag\n");
            bit_flag = NULL;
            return bit_flag;
        }
    }
    else{//bit_flag == NULL
        printf("Failed to allocate memory for bit_flag\n");
        bit_flag = NULL;
        return bit_flag;
    }
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position < 0) {
        printf("Invalid value, positive number only!!\n");
        return FAILURE;
    }
    bit* bit_flag = (bit*)hBit_flags;
    if(bit_flag == NULL){
        printf("Failed to allocate memory for bit_flag\n");
        return FAILURE;
    }

    if (flag_position > bit_flag -> capacity){
        if(fixSize(hBit_flags, flag_position) == FAILURE){
            return FAILURE;
        }
    }
    
    int array, bitNum, temp;
    array = flag_position / 32;
    bitNum = flag_position % 32;
    temp = 1 << bitNum;
    if ((bit_flag -> flag_holder[array] & temp) != temp) 
	{
		bit_flag -> flag_holder[array] += temp;
	}
    return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position < 0) {
        printf("Invalid value, positive number only!!\n");
        return FAILURE;
    }
    bit* bit_flag = (bit*)hBit_flags;
    if(bit_flag==NULL){
        printf("Failed to allocate memory for bit_flag\n");
        return FAILURE;
    }

    if (flag_position > bit_flag -> capacity){
        if(fixSize(hBit_flags, flag_position) == FAILURE){
            return FAILURE;
        }
    }
    
    int array, bitNum, temp;
    array = flag_position / 32;
    bitNum = flag_position % 32;
    temp = 1 << bitNum;

	if ((bit_flag -> flag_holder[array] & temp) == temp) 
	{
		bit_flag -> flag_holder[array] -= temp;
	}

    return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position < 0) {
        printf("Invalid value, positive number only!!");
        return -1;
    }
    bit* bit_flag = (bit*)hBit_flags;
    if(bit_flag==NULL){
        printf("Failed to allocate memory for bit_flag\n");
        return -1;
    }
    
    int array, bitNum, temp;
    array = flag_position / 32;
    bitNum = flag_position % 32;
    temp = 1 << bitNum;

    if (flag_position > bit_flag->capacity){
        return -1;
    }
    else if(((bit_flag->flag_holder[array]) & temp) == 0){
        return 0;
    }
    else
        return 1;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags){
    bit* bit_flag = (bit*)hBit_flags;
    if(bit_flag){
    return bit_flag->size;
    }
    else{
        return -1;
    }
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags){
    bit* bit_flag = (bit*)hBit_flags;
    if(bit_flag){
    return bit_flag -> capacity;
    }
    else{
        return -1;
    }
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags){
    bit* bit_flag = (bit*)*phBit_flags;
    if(bit_flag != NULL){
        free(bit_flag -> flag_holder);
        free(bit_flag);
    }
    *phBit_flags = NULL;
    return;
}

void bit_flags_display(BIT_FLAGS hBit_flags, unsigned int size){
    int i;
    for (i=0; i<=size; i++){
        printf("%d", bit_flags_check_flag(hBit_flags, i));
        if(i % 4 == 3){
            printf(" ");
        }
    }
    printf("\n");
    return;
}

Status fixSize(BIT_FLAGS hBit_flags,unsigned int flag_position){
 	bit* bit_flag = (bit*)hBit_flags;
    unsigned int* temp = (unsigned int*)malloc(sizeof(unsigned int));
    bit_flag -> capacity = flag_position;
    if (temp){
        *temp = *(bit_flag -> flag_holder);
        free(bit_flag -> flag_holder);
        bit_flag -> flag_holder = temp;
        bit_flag -> size = flag_position;
        return SUCCESS;
    }
    else{
        return FAILURE;
    }
    
}

