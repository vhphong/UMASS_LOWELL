/*********************************************************** 
Author: Hoang Do
Date: 9/19/2017
Effort: 20 min 
Purpose: Learn how to use '<<', unsign number and print unsign numeber
***********************************************************/

#include<stdio.h>

int main() {
	unsigned int x = 1;
	for (int i = 0; x != 0; i++) {
		printf("%d: %u\n", i, x);
		x = x << 1;
	}
	return 0;
}
