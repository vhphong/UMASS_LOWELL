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

struct node;
typedef struct node Node;
struct node
{
	char data;
	Node *next;
};
struct stack
{
	Node* head;
};
typedef struct stack Stack;
typedef Stack* Stackptr;

STACK stack_init_default(void)
{
	Stackptr pStack;
	pStack = (Stackptr)malloc(sizeof(Stack));
	if (pStack != NULL)
	{
		pStack->head = NULL;
	}
	return pStack;
}

Status stack_push(STACK hStack, char item)
{
	Stackptr pStack = (Stackptr)hStack;
	Node* temp;
	temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}
	temp->data = item;
	temp->next = pStack->head;
	pStack->head = temp;
	return SUCCESS;
}

Status stack_pop(STACK hStack)
{
	Stackptr pStack = (Stackptr)hStack;
	Node* temp;
	if (pStack->head == NULL)
	{
		return FAILURE;
	}
	temp = pStack->head;
	pStack->head = pStack->head->next;
	free(temp);
	return SUCCESS;
}

char stack_top(STACK hStack, Status* pStatus)
{
	Stack* pStack = (Stack*)hStack;
	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pStack->head->data;
} 


void stack_destroy(STACK* phStack)
{
	Stackptr pStack = (Stackptr)*phStack;
	Node* temp;
		while (pStack->head!=NULL)
		{
			temp = pStack->head;
			pStack->head = pStack->head->next;
			free(temp);
		}
	free(pStack);
	*phStack = NULL;
}

Boolean wordcompare(STACK hStack, char word[])
{
	Stackptr pStack = (Stackptr)hStack;
	if(pStack == NULL)
		return FALSE;
	int j = 0;
	char temp;
	while (word[j] != '\0')
	{
		if(word[j] == '{' || word[j] == '(' || word[j] == '[')
		{
			stack_push(pStack,word[j]);
		}
		else if(word[j] == '}' || word[j] == ')' || word[j] == ']')
		{
			if (pStack->head == NULL)
			{
				return FALSE;
			}
			temp = stack_top(pStack,NULL);
			if (temp == '{' && word[j] == '}')
				stack_pop(pStack);
			else if (temp == '(' && word[j] == ')')
				stack_pop(pStack);
			else if (temp == '[' && word[j] == ']')
				stack_pop(pStack);
			else
				return FALSE;
		}
		
		j++;
	}
	if(!stack_empty(pStack))
		return FALSE;
	else
		return TRUE;
	return TRUE;
}

Boolean stack_empty(STACK hStack)
{
	Stackptr pStack = (Stackptr)hStack;
	if (pStack->head == NULL)
	{
		return TRUE;
	}
	else
		return FALSE;
	return (Boolean)(pStack->head == NULL);
}


void clear_keyboard_buffer(void) 
{
	char ch;
	scanf("%c", &ch);
	while (ch != '\n') 
		scanf("%c", &ch);
	
}