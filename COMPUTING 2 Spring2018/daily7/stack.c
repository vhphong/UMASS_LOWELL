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

Status stack_push(pNode * head, char item)
{
	pNode temp;
	temp = (pNode)malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}
	temp->data = item;
	temp->next = *head;
	*head = temp;

	return SUCCESS;
}


/*checks for matching pair of char*/
Boolean isMatchingPair(char c1, char c2)
{
	if (c1 == '{' && c2 == '}')
		return TRUE;
	else if (c1 == '(' && c2 == ')')
		return TRUE;
	else if (c1 == '[' && c2 == ']')
		return TRUE;
	else
		return FALSE;
}


/*just to clear keybaord*/ 
void clear_keyboard_buffer(void) {
	char ch;
	int numOfConversion = scanf("%c", &ch);
	while (ch != '\n') 
		numOfConversion = scanf("%c", &ch);
	
}
/*pop function*/
char stack_pop(pNode * head)
{

	if (*head == NULL)
	{
		printf("Stack Empty \n");
		getchar();
		exit(0);
	}
	else
	{
		pNode temp = *head;
		*head = temp->next;
		return temp->data;
	}

}
/*checks if parenthesis is balanced or not and returns correct value*/
Boolean parenthesisBalanced(char ch[])
{
	int i = 0;
	Node *stack = NULL;
	while (ch[i])
	{
		if (ch[i] == '{' || ch[i] == '(' || ch[i] == '[')
			stack_push(&stack, ch[i]);

		if (ch[i] == '}' || ch[i] == ')' || ch[i] == ']')
		{
			if (stack == NULL)
			{
				return FALSE;
			}
			else if (!isMatchingPair(stack_pop(&stack), ch[i]))
			{
				return FALSE;
			}
		}
		i++;
	}

	if (stack == NULL)
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}
