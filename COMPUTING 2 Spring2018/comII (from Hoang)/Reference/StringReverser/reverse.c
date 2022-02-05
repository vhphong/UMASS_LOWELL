//****************************************
// 
//Program: Reverse function
//Author : Viet Tran Quoc Hoang 
//Date: 9/22/2016
//Time spent: 6 hours 
//Purpose: 
//Reverse a string passed by main using basic copy-and-paste method, attempt to calculate length internally
//****************************************//
#include <stdio.h>
#include <stdlib.h>


char* reverse(char *string){
	char temp;
	int length,head,tail;
	while(string[length]!='\0'){	
		length++;
	}
	
	tail = length -1;//shift 1 to left to avoid null terminator
	
	for(head=0;head<length/2;head++,tail--){//copy to middle of string array,adjust index number accordingly
		temp = string[head];
		string[head] = string[tail];
		string[tail] = temp;		
	}
	return string;
} 