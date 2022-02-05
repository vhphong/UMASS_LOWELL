/**********************************************************************
Program: Daily7
Author: Nhan Tran
Date: 10/11/2017
Time spent: 3 hours
Purpose: Using the stack working with the parenthesis
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


int main(int argc, char* argv[])
{
	int nline, i;
	STACK hStack = NULL;
	Status* pStatus = NULL;
	
	hStack = stack_init_default();
	if (hStack == NULL)
	{
		printf("Failed to create stack array.\n");
		exit(1);
	}
	
	scanf("%d", &nline);
	clear_keyboard_buffer();
	
	for (i = 0; i < nline; i++)
	{	
		if (Balanced(hStack, pStatus))
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}
		while (!stack_empty(hStack))
		{
			stack_pop(hStack);
		}
	}
	stack_destroy(&hStack);
	return 0;
}