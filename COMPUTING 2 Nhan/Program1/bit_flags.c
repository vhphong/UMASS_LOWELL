/***********************************************************
Author: Nhan Tran
Date: 10/19/2017
Effort: 12 hours
Purpose: Understand C bitwise operator and vector
***********************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

struct bit_flags
{
	int size;
	int capacity;
	unsigned int* flag_holder;
};
typedef struct bit_flags Bit_flags;
typedef Bit_flags* Bit_flags_ptr;

BIT_FLAGS bit_flags_init_number_of_bits( int number_of_bits)
{
    int num = number_of_bits;
	int num_int = 1;
	int i;
	num_int = (number_of_bits / 32) + 1;	    
	if(num < 0)
	{
		printf("Number is less than 0");
		return NULL;
	}
	Bit_flags_ptr pBit_flags = (Bit_flags_ptr)malloc(sizeof(Bit_flags));
	if(pBit_flags != NULL)
	{
		pBit_flags->size = num;
		pBit_flags->capacity = num_int * 32;
		pBit_flags->flag_holder = (unsigned int*)malloc(sizeof(unsigned int)*num_int);
		if(pBit_flags->flag_holder == NULL)
		{
			free(pBit_flags);
			return NULL;
		}
		else
		{
			for(i = 0; i < num_int; i++)
			{
				pBit_flags->flag_holder[i] = 0;
			}
			return pBit_flags;
		}
	}
	else
	{
		free(pBit_flags);
		return NULL;
	}
}
Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags_ptr pBit_flags = (Bit_flags_ptr) hBit_flags;
	if(pBit_flags == NULL)
		return FAILURE;
	unsigned int *temp;
	int i, p, j = 1,k;
	i = flag_position / 32;
	p = flag_position % 32;
	j = j << p;
	if(flag_position < 0)
	{
		printf("Number is less than 0");
		return FAILURE;
	}
 	else if(flag_position > pBit_flags->capacity)
	{
		temp = (unsigned int*)malloc(sizeof(unsigned int) * (i+1));
		if (temp == NULL)
			return FAILURE;
		for(k = 0; k <= (pBit_flags->capacity); k++)
		{
			if(bit_flags_check_flag(hBit_flags,k) == 1)
			{
				(temp[k/32]) |= 1 << (k%32);
			}
		}
		free(pBit_flags->flag_holder);
		pBit_flags->flag_holder = temp;
		pBit_flags->capacity = (i+1) * 32;
		pBit_flags->size = flag_position;
	} 
	else if (flag_position > pBit_flags->size)
	{
		pBit_flags->size = flag_position;
	}
	pBit_flags->flag_holder[i] = pBit_flags->flag_holder[i] | j;
	return SUCCESS;
}
Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags_ptr pBit_flags = (Bit_flags_ptr) hBit_flags;
	if(pBit_flags == NULL)
		return FAILURE;
	int num = flag_position;
	int i, p, j = 1,k;
	unsigned int *temp;
	i = flag_position / 32;
	p = flag_position % 32;
	j = j << p;
	j = ~j;
	if(num < 0)
	{
		printf("Number is less than 0");
		return FAILURE;
	}
	else if(flag_position > pBit_flags->capacity)
	{
		temp = (unsigned int*)malloc(sizeof(unsigned int) * (i+1));
		if (temp == NULL)
			return FAILURE;
		for(k = 0; k <= (pBit_flags->capacity); k++)
		{
			if(bit_flags_check_flag(hBit_flags,k) == 1)
			{
				(temp[k/32]) |= 1 << (k%32);
			}
		}
		free(pBit_flags->flag_holder);
		pBit_flags->flag_holder = temp;
		pBit_flags->capacity = (i+1) * 32;
		pBit_flags->size = flag_position;
	} 
	else if (flag_position > pBit_flags->size)
	{
		pBit_flags->size = flag_position;
	}
	pBit_flags->flag_holder[i] = pBit_flags->flag_holder[i] & j;
	return SUCCESS;

}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags_ptr pBit_flags = (Bit_flags_ptr) hBit_flags;
	if(pBit_flags == NULL)
		return -1;
	if (flag_position < 0)
		return -1;
	int i, p, j = 1;	
	i = flag_position / 32;
	p = flag_position % 32;
	j = j << p;
	if (flag_position > pBit_flags->capacity)
	{
		return -1;
	}
	else if( (j & pBit_flags->flag_holder[i] ) != 0)
		return 1;
	else 
		return 0;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags_ptr pBit_flags = (Bit_flags_ptr) hBit_flags;
	if(pBit_flags == NULL)
		return -1;
	return pBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags_ptr pBit_flags = (Bit_flags_ptr) hBit_flags;
	if(pBit_flags == NULL)
		return -1;
	return pBit_flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags_ptr pBit_flags = (Bit_flags_ptr) *phBit_flags;
	free(pBit_flags->flag_holder);
	free(pBit_flags);
	*phBit_flags = NULL; 
}

void bit_flags_display(BIT_FLAGS hBit_flags,unsigned int size)
{
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
