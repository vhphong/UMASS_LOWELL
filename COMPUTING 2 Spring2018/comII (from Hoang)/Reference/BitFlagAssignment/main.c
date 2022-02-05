//
//  main.c
//  A1_vtran
//
//  Created by Viet Tran Quoc Hoang on 2/10/16.
//  Copyright © 2016 Viet Tran Quoc Hoang. All rights reserved.
//

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
