
#include <stdlib.h>
#include "bit_flags.h"

int maxBits = 32;

struct bit_flags
{
	int size;
	int capacity;
	int *data;
};
typedef struct bit_flags Bit_flags;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	int i;
	if (number_of_bits <= 0) {
		return NULL;
	}

	Bit_flags* pBit_flags;
	pBit_flags = (Bit_flags*)malloc(sizeof(Bit_flags));

	if (pBit_flags != NULL) {
		pBit_flags->size = number_of_bits / maxBits;
		pBit_flags->capacity = pBit_flags->size + 1;
		pBit_flags->data = malloc(sizeof(int)*pBit_flags->capacity);
		if (pBit_flags->data == NULL)
		{
			free(pBit_flags);
			pBit_flags = NULL;
		}
	}
	for (i = 0; i <= pBit_flags->capacity/32; i++) {
		pBit_flags->data[i] = 0;
	}
	return (BIT_FLAGS)pBit_flags;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int i;
	int *temp;
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	int arrayIndex = flag_position / maxBits;
	int bitPosition = flag_position % maxBits;
	if (flag_position <= 0 && pBit_flags == NULL) {
		return FAILURE;
	}

	if (flag_position >= pBit_flags->capacity*maxBits) {
		temp = malloc(sizeof(int) * (arrayIndex+1));
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i <= arrayIndex; i++) {
			if (i <= pBit_flags->capacity/32) {
				temp[i] = pBit_flags->data[i];
			}
			else 
			{
				break;
			}
		}
		free(pBit_flags->data);

		pBit_flags->data = temp;
		pBit_flags->capacity *= (pBit_flags->size+1);
	}
	if (flag_position>pBit_flags->size)
	{
		pBit_flags->size = flag_position;
	}
	pBit_flags->data[arrayIndex] |= (1 << bitPosition);
	return SUCCESS;
}

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	int i;
	int *temp;
	int arrayIndex = flag_position / maxBits;
	int bitPosition = flag_position % maxBits;
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	if (flag_position <= 0 || pBit_flags == NULL) {
		return FAILURE;
	}
	if (flag_position >= pBit_flags->capacity*maxBits) {
		temp = malloc(sizeof(int) * (arrayIndex+1));
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i <= arrayIndex; i++) {
			temp[i] = pBit_flags->data[i];
		}
		free(pBit_flags->data);
		pBit_flags->capacity *= (pBit_flags->size+1);
		pBit_flags->data = temp;
	}

	if (flag_position>pBit_flags->size)
	{
		pBit_flags->size = flag_position;
	}
	return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	Bit_flags* pBit_flags = (Bit_flags*)hBit_flags;
	int arrayIndex, bitPosition, checker;

	arrayIndex = flag_position / maxBits;
	bitPosition = flag_position % maxBits;

	checker = pBit_flags->data[arrayIndex];

	return (checker>>=bitPosition)&1;
}
int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	Bit_flags* phBit_flags = (Bit_flags*)hBit_flags;
	return phBit_flags->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	Bit_flags* phBit_flags = (Bit_flags*)hBit_flags;
	return phBit_flags->capacity * maxBits;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	Bit_flags* pBit_flags = (Bit_flags*)*phBit_flags;
	free(pBit_flags->data);
	free(*phBit_flags);
	*phBit_flags = NULL;
}
