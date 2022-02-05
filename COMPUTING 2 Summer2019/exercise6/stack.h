/**********************************************************************
Program:  exercise 6
Author:  Phong Vo
Date:    07/29/2019
Time spent:  3 days
Purpose: to learn more about the roles of stack and linked list
***********************************************************************/
#ifndef STACK_H
#define STACK_H

#include "status.h"

typedef void* STACK;
STACK stack_init_default(void);
Status stack_push(STACK hStack, char item);
Status stack_pop(STACK hStack);
char stack_top(STACK hStack, Status* pStatus);

Boolean parentheses_fitting(STACK hStack, char word[]);
void stack_destroy(STACK* phStack);
Boolean stack_empty(STACK hStack);
void clear_keyboard_buffer(void);

#endifndif