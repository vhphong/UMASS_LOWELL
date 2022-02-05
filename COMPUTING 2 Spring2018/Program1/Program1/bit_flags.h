/***********************************************************
Author: Phong Vo
Date: 02/18/2018
Effort: 10 hrs
Purpose: Program 1 project
Interface proposal:
***********************************************************/

#ifndef BIT_FLAGS_H
#define BIT_FLAGS_H
#include "status.h"

typedef void* BIT_FLAGS;

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits);

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position);

Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position);

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position);

//Precondition: hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the number of bits currently held by the data structure.
int bit_flags_get_size(BIT_FLAGS hBit_flags);

//Precondition: hBit_flags is a handle to a valid Bit_flags object.
//Postcondition: returns the number of bits the object CAN hold.
int bit_flags_get_capacity(BIT_FLAGS hBit_flags);

//Precondition: phBit_flags is the address of a handle to a valid Bit_flags object.
//Postcondition: The memory for the object referred to by the handle is free'd and the handle is set to NULL.
void bit_flags_destroy(BIT_FLAGS* phBit_flags);

#endif /* BIT_FLAGS_H_ */

