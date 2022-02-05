#include "bit_flags.h"
#include<stdio.h>
int main(int argc, const char * argv[])
{
	int i = 0;
	int j;
	BIT_FLAGS hBit_flags = NULL;
	hBit_flags = bit_flags_init_number_of_bits(1);
	printf("total size: %d\n", bit_flags_get_size(hBit_flags));
	printf("total capacity: %d\n", bit_flags_get_capacity(hBit_flags));
	if (hBit_flags == NULL) {
		printf("Fail allocation\n");
	}
	bit_flags_set_flag(hBit_flags, 3);
	bit_flags_set_flag(hBit_flags, 16);
	bit_flags_set_flag(hBit_flags, 31);
	

	bit_flags_set_flag(hBit_flags, 87);


	printf("%d", bit_flags_get_capacity);
	j = bit_flags_get_capacity(hBit_flags) - 1;
	while (i<bit_flags_get_capacity(hBit_flags))
	{
		printf("%d", bit_flags_check_flag(hBit_flags, i));
		if (j % 4 == 0)
		{
			printf(" ");
		}
		if (j % 32 == 0)
		{
			printf("\n");
		}

		i++;
		j--;
	}
	printf("\n\n");
	bit_flags_unset_flag(hBit_flags, 31);
	bit_flags_unset_flag(hBit_flags, 3);
	bit_flags_set_flag(hBit_flags, 99);
	bit_flags_set_flag(hBit_flags, 100);
	i = 0;
	while (i<bit_flags_get_capacity(hBit_flags))
	{
		printf("%d", bit_flags_check_flag(hBit_flags, i));
		if (j % 4 == 0)
		{
			printf(" ");
		}
		if (j % 32 == 0)
		{
			printf("\n");
		}

		i++;
		j--;
	}
	printf("total size: %d\n", bit_flags_get_size(hBit_flags));
	printf("total capacity: %d\n", bit_flags_get_capacity(hBit_flags));

	bit_flags_destroy(&hBit_flags);
	return 0;
}