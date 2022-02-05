/**********************************************************************
Program: Daily7
Author: Nhan Tran
Date: 10/11/2017
Time spent: 3 hours
Purpose: Using the stack working with the parenthesis
***********************************************************************/

#ifndef STACK_H
#define STACK_H

enum status { FAILURE, SUCCESS };
typedef enum status Status;

enum boolean { FALSE, TRUE };
typedef enum boolean Boolean;

typedef void* STACK;

STACK stack_init_default(void);

Status stack_push(STACK hStack, char item);

Status stack_pop(STACK hStack);

char stack_top(STACK hStack, Status* pStatus);

Boolean stack_empty(STACK hStack);

Boolean Balanced(STACK hStack, Status* pStatus);

void stack_destroy(STACK* phStack);

void clear_keyboard_buffer(void);

#endif
