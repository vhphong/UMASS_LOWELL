/*********************************************************** 
Author: Hoang Do 
Date: 10/01/2017 
Effort: 2 hours 
Purpose: <Purpose of this assignment in your own words> 
Interface proposal: <answer the last question in the specification> 
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "bit_flags.h"
void bit_flags_display(BIT_FLAGS hBit_flags,int size);
int main(int argc, const char * argv[]) {
    
    BIT_FLAGS flag_holder;
    flag_holder= bit_flags_init_number_of_bits(4);
    bit_flags_display(flag_holder, bit_flags_get_size(flag_holder));
    bit_flags_set_flag(flag_holder,1);
    bit_flags_set_flag(flag_holder,3);
    bit_flags_set_flag(flag_holder,2);
    bit_flags_set_flag(flag_holder,5);
    bit_flags_set_flag(flag_holder,3);
    bit_flags_display(flag_holder, 5);
    bit_flags_set_flag(flag_holder,8);
    bit_flags_display(flag_holder, 8);
    bit_flags_set_flag(flag_holder, 15);
    bit_flags_display(flag_holder, bit_flags_get_size(flag_holder));
    bit_flags_unset_flag(flag_holder, 3);
    bit_flags_unset_flag(flag_holder, 5);
    bit_flags_display(flag_holder, bit_flags_get_size(flag_holder));
    bit_flags_unset_flag(flag_holder, 8);
    bit_flags_display(flag_holder, bit_flags_get_size(flag_holder));
    bit_flags_unset_flag(flag_holder, 18);
    bit_flags_display(flag_holder, bit_flags_get_size(flag_holder));
    bit_flags_destroy(&flag_holder);
    return 0;
}
