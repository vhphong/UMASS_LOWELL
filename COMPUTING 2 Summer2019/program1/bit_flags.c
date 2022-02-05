/***********************************************************
Author: Phong Vo
Date: 07/22/2019
Effort: 20 hrs
Purpose: Understand bitwise operator and vector
Interface proposal: The interface displays arrays of bits.
					The other function converts a decimal number to 
					binary number by setting to 1 and resetting to 0
						the corresponding bits.
***********************************************************/ 

#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "bit_flags.h"

struct Bit_Flags{ // Bit_Flags
    unsigned int* flag_holder;
    int size;
    int capacity;
};

typedef struct Bit_Flags bitFlags;
void bit_flags_display(BIT_FLAGS hBit_flags, unsigned int size);
Status fixSize(BIT_FLAGS hBit_flags, unsigned int new_size);

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits){
	bitFlags* bit_flags = (bitFlags*)malloc(sizeof(bitFlags));
    if (number_of_bits < 0){
        printf("Error because number of bit is less than 0. \n");
        bit_flags = NULL;
        return bit_flags;
    }
    if (bit_flags){
        bit_flags->size = number_of_bits;
        bit_flags->capacity = (bit_flags->size) + 1;
        bit_flags->flag_holder = (unsigned int*)malloc(sizeof(unsigned int)*1);
        if (bit_flags->flag_holder){
            bit_flags->flag_holder[0] = 0;
            return bit_flags;
        }
        else {
            free(bit_flags);
            printf("Failed to allocate memory for bit_flag\n");
            bit_flags = NULL;
            return bit_flags;
        }
    }
    else {   //bit_flags == NULL
        printf("Failed to allocate memory for bit_flag\n");
        bit_flags = NULL;
        return bit_flags;
    }
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position < 0) {
        printf("Invalid value, positive number only!!\n");
        return FAILURE;
    }
    bitFlags* bit_flag = (bitFlags*)hBit_flags;
    if(bit_flag == NULL){
        printf("Failed to allocate memory for bit_flag\n");
        return FAILURE;
    }

    if (flag_position > bit_flag->capacity){
        if(fixSize(hBit_flags, flag_position) == FAILURE){
            return FAILURE;
        }
    }
    
    int array, bitNum, temp;
    array = flag_position / 32;
    bitNum = flag_position % 32;
    temp = 1 << bitNum;
    if ((bit_flag->flag_holder[array] & temp) != temp) 
	{
		bit_flag->flag_holder[array] += temp;
	}
    return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position < 0) {
        printf("Invalid value, positive number only!!\n");
        return FAILURE;
    }
    bitFlags* bit_flag = (bitFlags*)hBit_flags;
    if(bit_flag == NULL){
        printf("Failed to allocate memory for bit_flag\n");
        return FAILURE;
    }

    if (flag_position > bit_flag->capacity){
        if(fixSize(hBit_flags, flag_position) == FAILURE){
            return FAILURE;
        }
    }
    
    int array = flag_position / 32;
    int bitNum = flag_position % 32;
    int temp = 1 << bitNum;

	if ((bit_flag->flag_holder[array] & temp) == temp) 
		bit_flag->flag_holder[array] -= temp;
    return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position){
    if (flag_position < 0) {
        printf("Invalid value, positive number only!!");
        return -1;
    }
    bitFlags* bit_flag = (bitFlags*)hBit_flags;
    if (bit_flag == NULL){
        printf("Failed to allocate memory for bit_flag\n");
        return -1;
    }
    
    int array = flag_position / 32;
    int bitNum = flag_position % 32;
    int temp = 1 << bitNum;

    if (flag_position > bit_flag->capacity)
        return -1;
    else if (((bit_flag->flag_holder[array]) & temp) == 0)
        return 0;
    else
        return 1;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags){
    bitFlags* bit_flag = (bitFlags*)hBit_flags;
    if (bit_flag) // if bit_flag != NULL
        return bit_flag->size;
    else
        return -1;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags){
    bitFlags* bit_flag = (bitFlags*)hBit_flags;
    if (bit_flag) // if bit_flag != NULL
        return bit_flag -> capacity;
    else
        return -1;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags){
    bitFlags* bit_flag = (bitFlags*)*phBit_flags;
    if (bit_flag != NULL){
        free(bit_flag -> flag_holder);
        free(bit_flag);
    }
    *phBit_flags = NULL;
    return;
}

void bit_flags_display(BIT_FLAGS hBit_flags, unsigned int size){
    for (int i=0; i<=size; i++){
        printf("%d", bit_flags_check_flag(hBit_flags, i));
        // splits into groups of 4 bits
        if (i % 4 == 3){
            printf(" ");
        }
    }
    printf("\n");
    return;
}

Status fixSize(BIT_FLAGS hBit_flags,unsigned int flag_position){
 	bitFlags* bit_flag = (bitFlags*)hBit_flags;
    unsigned int* temp = (unsigned int*)malloc(sizeof(unsigned int));
    bit_flag->capacity = flag_position;
    if (temp){
        *temp = *(bit_flag->flag_holder);
        free(bit_flag->flag_holder);
        bit_flag->flag_holder = temp;
        bit_flag->size = flag_position;
        return SUCCESS;
    }
    else {
        return FAILURE;
    }
    
}