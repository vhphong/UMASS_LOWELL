/**********************************************************************
Program:  exercise 6
Author:  Phong Vo
Date:    07/29/2019
Time spent:  3 days
Purpose: to learn more about the roles of stack and linked list
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char* argv[]){
	int num;
	int strLen = 128;
	char c_string[strLen];
	Boolean result;
	
	scanf("%d", &num);
	clear_keyboard_buffer();
	
	for(int i = 0; i < num; i++){
		STACK hStack = stack_init_default();;
		if (hStack == NULL){
			printf("Failed to allocate memory \n");
			exit(1);
		}
		fgets(c_string, strLen, stdin);
		if (c_string[0] == '\n'){
			result = TRUE;
		}
		else{
			result =  parentheses_fitting(hStack, c_string);
		}
		
		if (result == TRUE){
			printf("Yes\n");
		}
		else {
			printf("No\n");
		}
		c_string[0] = '\0';
		stack_destroy(&hStack);
	}		
	return 0;		
} 0;		
}}