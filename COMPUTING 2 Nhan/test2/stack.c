/**********************************************************************
Program: Daily7
Author: Nhan Tran
Date: 10/27/2017
Time spent: 3 hours
Purpose: Using the stack working with the parenthesis
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

struct node
{
	char data;
	struct node *next;
};
typedef struct node Node;

struct stack
{
	Node* head;
};
typedef struct stack Stack;

void clear_keyboard_buffer(void) {
	char ch;

	scanf("%c", &ch);
	while (ch != '\n')
	{
		scanf("%c", &ch);
	}
}

STACK stack_init_default(void)
{
	Stack* pStack;
	pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL)
	{
		pStack->head = NULL;
	}
	return pStack;
}

Status stack_push(STACK hStack, char item)
{
	Stack* pStack = (Stack*)hStack;
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
	Stack* pStack = (Stack*)hStack;
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
	
	if (stack_empty(hStack))
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return -1;
	}

	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pStack->head->data;
}

Boolean stack_empty(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;

	return (Boolean)(pStack->head == NULL);
}

void stack_destroy(STACK* phStack)
{
	Stack* pStack = (Stack*)*phStack;
	Node* temp;

	if (pStack != NULL)
	{
		while (pStack->head != NULL)
		{
			temp = pStack->head;
			pStack->head = pStack->head->next;
			free(temp);
		}
		free(pStack);
		*phStack = NULL;
	}
}

Boolean Balanced(STACK hStack, Status* pStatus)
{
	char ch;
	ch = getchar();
	while (ch != '\n' && ch != EOF)
	{
		if (ch == '(' || ch == '[' || ch == '{')
		{
			stack_push(hStack, ch);
		}
			else
		{
			if (stack_empty(hStack))
			{
				stack_push(hStack, ch);
			}
			if (stack_top(hStack, pStatus) == '(' && ch == ')')
			{
				stack_pop(hStack);
			}
			if (stack_top(hStack, pStatus) == '[' && ch == ']')
			{
				stack_pop(hStack);
			}
			if (stack_top(hStack, pStatus) == '{' && ch == '}')
			{
				stack_pop(hStack);
			}
		}
		ch = getchar();
	}
	return (Boolean)(stack_empty(hStack) == TRUE);
}

