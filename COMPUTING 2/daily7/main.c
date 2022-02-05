/***********************************************************
Author: Phong Vo
Date: 02/23/2018
Effort: 10 hrs
Purpose: daily7
Interface proposal: 
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main(int argc, char* argv[])
{
	int size, i;
	Boolean result;
	char arr[100];
	
	scanf("%d", &size);
	clear_keyboard_buffer();
	
	for (i = 0; i < size; i++)
	{
		scanf("%s", arr);
		result = parenthesisBalanced(arr);
		if (result == TRUE)
		{
			printf("Yes\n");
		}
		else if (result == FALSE)
		{
			printf("No\n");
		}
		clear_keyboard_buffer();
	}
	return 0;
}


