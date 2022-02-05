/***********************************************
Author: Phong Vo
Date: 7-11-2019
Effort: 10 minutes
Purpose:
    To understand the "<<" operator as it
    shifts the value of the bit over by 1,
    a.k.a multiple by 2 at each shifting left by 1.
***********************************************/

#include <stdio.h>
// #include <stdlib.h>

int main(int argc, char* agrv[]){
    unsigned x = 1;
    for (int i=0; x!=0 ; i++){
    	printf("%d: %u \n", i, x);
        x = x << 1;
	}
    return 0;
}