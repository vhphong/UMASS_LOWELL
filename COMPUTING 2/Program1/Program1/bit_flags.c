/***********************************************************
Author: Phong Vo
Date: 02/18/2018
Effort: 10 hrs
Purpose: Program 1 project
Interface proposal:
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"

typedef struct bit_flags
{
	int size;
	int capacity;
	int *bit;
} Bit_flags;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	Bit_flags* pBit_flags;
	if (number_of_bits > 0)   // The given number is positive
	{
		pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));
		if (pBit_flags != NULL)
		{
			pBit_flags->capacity = sizeof(int);
			pBit_flags->size = number_of_bits;
			pBit_flags->bit = (int*)malloc(sizeof(int));
			if (pBit_flags->bit != NULL)
			{
				*pBit_flags->bit = 0;
			}
			else
			{
				printf("Could not set memory for bit value.\n");
				pBit_flags = NULL;
			}
		}
		printf("Bit flags object memory print created!\n\n");
	}
	else   // Given number was 0 or negative
	{
		printf("Number of bits cannot be negative.\n");
		pBit_flags = NULL;
	}

	return pBit_flags;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Status stat;
	int bit_to_set = flag_position;
	int* temp;
	Bit_flags* phBit_flags = (Bit_flags*)hBit_flags;   // Cast the void* object to a Bit_flag* object

	while (flag_position >= phBit_flags->capacity)   // While the flag position is bigger than what the object can handle
	{
		phBit_flags->capacity *= 2;   // Double its capacity
		temp = (int*)malloc(sizeof(int) * phBit_flags->capacity);   // Get new dynamic array with new capacity
		if (temp != NULL)   // Check if malloc worked
		{
			*temp = *(phBit_flags->bit);
			free(phBit_flags->bit);       // Free the dynamic arrays that is too small to hold the requested bit
			phBit_flags->bit = temp;
		}
		else   // Malloc failed
		{
			stat = FAILURE;
			printf("Could not resize bit flags object.\n");
			return stat;
		}
	}

	flag_position /= phBit_flags->capacity;
	phBit_flags->bit[flag_position] |= 1 << (bit_to_set%phBit_flags->capacity);   // Set the bit to the object
	phBit_flags->size--;   // Keep count of how many bits have been set

	stat = SUCCESS;
	printf("Bit set\n");

	return stat;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Status stat;
	int bit_to_set = flag_position;
	int* temp;
	Bit_flags* phBit_flags = (Bit_flags*)hBit_flags;

	while (flag_position >= phBit_flags->capacity)
	{
		phBit_flags->capacity *= 2;
		temp = (int*)malloc(sizeof(int) * phBit_flags->capacity);
		if (temp != NULL)
		{
			*temp = *(phBit_flags->bit);
			free(phBit_flags->bit);
			phBit_flags->bit = temp;
		}
		else
		{
			stat = FAILURE;
			printf("Could not resize bit flags object.\n");
			return stat;
		}
	}

	flag_position /= phBit_flags->capacity;
	phBit_flags->bit[flag_position] &= ~(1 << (bit_to_set%phBit_flags->capacity));
	phBit_flags->size++;

	stat = SUCCESS;
	printf("Bit clear\n");

	return stat;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int bit, bit_set = flag_position;
	Bit_flags* phBit_flags = (Bit_flags*)hBit_flags;

	if (flag_position < 0 || flag_position > phBit_flags->capacity)   // If the requested check is out-of-bounds
		bit = -1;   // Return error

	else   // Return bit requested
	{
		flag_position /= phBit_flags->capacity;
		if ((phBit_flags->bit[flag_position] >> bit_set) & 1)
		{
			bit = phBit_flags->bit[flag_position];
		}
	}

	return bit;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* phBit_flags = (Bit_flags*)hBit_flags;
	return phBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* phBit_flags = (Bit_flags*)hBit_flags;
	return phBit_flags->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pphBit_flags = (Bit_flags*)*phBit_flags;
	if (pphBit_flags != NULL)
	{
		free(pphBit_flags->bit);
		free(pphBit_flags);
	}
	pphBit_flags = NULL;

	printf("Bit flags object memory print destroyed!\n");
}