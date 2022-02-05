/**********************************************************************
Program: Daily7
Author: Nhan Tran
Date: 10-27-2017
Time spent: 3 days
Purpose: The purpose of this program is to understand stack linked list
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char* argv[])
{
 	
	int num,i;
	scanf("%d",&num);
	clear_keyboard_buffer();
	char word[128];
	for( i = 0; i < num ; i++)
	{	
		STACK hStack = NULL;
		Boolean result;
		hStack = stack_init_default();
		if(hStack == NULL)
		{
			printf("Fail to allocate memory\n");
			exit(1);
		}
		fgets(word,128,stdin);
		if(word[0] == '\n')
			result = TRUE;
		else
			result =  wordcompare(hStack,word);
		if (result == TRUE)
		{
			printf("Yes\n");
		}
		else if (result == FALSE)
		{
			printf("No\n");
		}
		word[0] = '\0';
		stack_destroy(&hStack);
	}		
	return 0;		
}