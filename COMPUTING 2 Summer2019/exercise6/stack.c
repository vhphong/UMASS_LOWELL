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

typedef struct node Node;
struct node{
	char data;
	Node *next;
};

typedef struct stack Stack;
struct stack{
	Node* head;
};
typedef Stack* my_stack;

STACK stack_init_default(void){
	my_stack pStack = (my_stack)malloc(sizeof(Stack));
	if (pStack){
		pStack->head = NULL;
	}
	return pStack;
}

Status stack_push(STACK hStack, char item){
	my_stack pStack = (my_stack)hStack;
	Node* temp = (Node*)malloc(sizeof(Node));
	if (!temp){
		printf("Failed to allocate memory. \n");
		return FAILURE;
	}
	temp->data = item;
	temp->next = pStack->head;
	pStack->head = temp;
	return SUCCESS;
}

Status stack_pop(STACK hStack){
	my_stack pStack = (my_stack)hStack;
	if (!pStack->head){
		printf("Failed to allocate memory. \n");
		return FAILURE;
	}
	Node* temp = pStack->head;
	pStack->head = pStack->head->next;
	free(temp);
	return SUCCESS;
}

char stack_top(STACK hStack, Status* pStatus){
	Stack* pStack = (Stack*)hStack;
	if (pStatus){
		*pStatus = SUCCESS;
	}
	return pStack->head->data;
} 

void stack_destroy(STACK* phStack){
	my_stack pStack = (my_stack)*phStack;
	Node* temp;
		while (pStack->head){
			temp = pStack->head;
			pStack->head = pStack->head->next;
			free(temp);
		}
	free(pStack);
	*phStack = NULL;
}

Boolean parentheses_fitting(STACK hStack, char word[]){
	my_stack pStack = (my_stack)hStack;
	if (pStack == NULL){
		printf("Failed to allocate memory. \n");
		return FALSE;
	}
	int i = 0;
	char temp;
	while (word[i] != '\0'){
		if(word[i] == '{' || word[i] == '(' || word[i] == '['){
			stack_push(pStack, word[i]);
		}
		else if(word[i] == '}' || word[i] == ')' || word[i] == ']'){
			if (pStack->head == NULL)
				return FALSE;
			
			temp = stack_top(pStack, NULL);
			if (temp == '{' && word[i] == '}')
				stack_pop(pStack);
			else if (temp == '(' && word[i] == ')')
				stack_pop(pStack);
			else if (temp == '[' && word[i] == ']')
				stack_pop(pStack);
			else
				return FALSE;
		}
		++i;
	}
	if(!stack_empty(pStack))
		return FALSE;
	else
		return TRUE;
	return TRUE;
}

Boolean stack_empty(STACK hStack){
	my_stack pStack = (my_stack)hStack;
	if (pStack->head == NULL)
		return TRUE;
	else
		return FALSE;
	return (Boolean)(pStack->head == NULL);
}

void clear_keyboard_buffer(void){
	char myChar;
	scanf("%c", &myChar);
	while (myChar != '\n') 
		scanf("%c", &myChar);
	
}
} &myChar);
	
}\n') 
		scanf("%c", &ch);
	
} '\n') 
		scanf("%c", &ch);
	
}