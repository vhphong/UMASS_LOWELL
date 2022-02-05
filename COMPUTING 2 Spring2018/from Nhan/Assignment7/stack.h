/**********************************************************************
Program: Daily7
Author: Nhan Tran
Date: 10-27-2017
Time spent: 3 days
Purpose: The purpose of this program is to understand stack linked list
***********************************************************************/
#ifndef STACK_H
#define STACK_H

#include "status.h"

typedef void* STACK;
STACK stack_init_default(void);

Status stack_push(STACK hStack, char item);

Status stack_pop(STACK hStack);

char stack_top(STACK hStack, Status* pStatus);


Boolean wordcompare(STACK hStack, char word[]);

void stack_destroy(STACK* phStack);

Boolean stack_empty(STACK hStack);

void clear_keyboard_buffer(void);
#endif