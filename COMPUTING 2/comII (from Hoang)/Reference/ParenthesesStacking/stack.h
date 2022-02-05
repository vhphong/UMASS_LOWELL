/**********************************************************************
 Program: Daily 7
 Author: Viet Tran Quoc Hoang
 Date: 2/27/2016
 Time spent: 2 days
 Purpose: Implementation of stack using linked lists based on parentheses problem
 ***********************************************************************/
#ifndef stack_h
#define stack_h

#include "status.h"

struct public_stack;
typedef struct public_stack Public_stack;
typedef Public_stack* STACK;

struct public_stack{
    Status(*push)(STACK hStack, char item);
    Status(*pop_top)(STACK hStack);
    Status(*pop_item)(STACK hStack, char item);
    char(*top)(STACK hStack,Status* pStatus);
    Boolean(*empty)(STACK hStack);
    void(*destroy)(STACK* phStack);
    void(*print)(STACK hStack);
};

STACK stack_init_default(void);
Status stack_push(STACK hStack,char item);
Status stack_pop_top(STACK hStack);
Status stack_pop_item(STACK hStack,char item);
char stack_top(STACK hStack,Status* pStatus);
Boolean stack_empty(STACK hStack);
void stack_destroy(STACK* phStack);
void stack_print(STACK hStack);
#endif /* stack_h */
