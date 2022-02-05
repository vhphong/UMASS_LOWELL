/**********************************************************************
 Program: Daily 7
 Author: Viet Tran Quoc Hoang
 Date: 2/27/2016
 Time spent: 2 days
 Purpose: Implementation of stack using linked lists based on parentheses problem
 ***********************************************************************/
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>


struct node;
typedef struct node Node;
typedef Node* pNode;

struct node{
    char data;
    Node* next;
};

struct stack{
    Status(*push)(STACK hStack, char item);
    Status(*pop_top)(STACK hStack);
    Status(*pop_item)(STACK hStack,char item);
    char(*top)(STACK hStack,Status* pStatus);
    Boolean(*empty)(STACK hStack);
    void(*destroy)(STACK* phStack);
    void(*print)(STACK hStack);
    
    Node* head;
};
typedef struct stack Stack;

STACK  stack_init_default(void){
     Stack* pStack;
    pStack = (Stack*)malloc(sizeof(Stack));
    if(pStack){
        pStack->push = stack_push;
        pStack->pop_top = stack_pop_top;
        pStack->pop_item = stack_pop_item;
        pStack->top = stack_top;
        pStack->empty = stack_empty;
        pStack->destroy =stack_destroy;
        pStack->print = stack_print;
        
        pStack->head = NULL;
        return(STACK)pStack;
    }
    return NULL;
}

Status stack_push(STACK hStack,char item){
    Stack* pStack = (Stack*)hStack;
    Node* temp;
    temp = (Node*)malloc(sizeof(Node));
    if (temp == NULL){
        return FAILURE;
    }
    temp->data = item;
    temp->next = pStack->head;
    pStack->head = temp;
    return SUCCESS;
}

Status stack_pop_top(STACK hStack){
    Stack* pStack = (Stack*)hStack;
    if(pStack->head == NULL){
        //printf("empty stack\n");
        return FAILURE;
    }
    Node* temp=pStack->head;
    pStack->head = temp->next;
    free(temp);
    return SUCCESS;
}

Status stack_pop_item(STACK hStack,char item){
    Stack* pStack = (Stack*)hStack;
    if (pStack->head == NULL) {
        //printf("stack is already empty, cant pop %c\n",item);
        return FAILURE;
    }
    Node* current = pStack->head;
    Node* prev = NULL;
    
	if (current->data == item) {
		if (prev == NULL) {//if beginning of list, pop top
			pStack->head  = current->next;//can also use pop top function hStack->pop_top(hStack)
		}
		else{
			//printf("Item not at the top\n");
			return FAILURE;
		}
		free(current);
		//printf("popped item %c\n",item);
		return SUCCESS;
	}
    //printf("Top item %c does not match\n",item);
    return FAILURE;
}

char stack_top(STACK hStack,Status* pStatus){
    Stack* pStack = (Stack*)hStack;
    if (pStack->head == NULL){
        *pStatus = FAILURE;
        return 'E';
    }
    *pStatus = SUCCESS;
    return pStack->head->data;
}

Boolean stack_empty(STACK hStack){
    Stack* pStack = (Stack*)hStack;
    return(Boolean)(pStack->head == NULL);
}

void stack_destroy(STACK* phStack){
    Stack* pStack = (Stack*)*phStack;
    while(pStack->head!=NULL){
        Node* temp;
        temp = pStack->head;
        pStack->head = pStack->head->next;
        free(temp);
        }
    free(*phStack);
    *phStack = NULL;
    return;
}

void stack_print(STACK hStack){
    Stack* pStack = (Stack*)hStack;
    if (pStack->head == NULL){
        printf("empty stack\n");
        return;
    }
    Node* temp = pStack->head;
    do{
        printf("%c",temp->data);
        temp = temp->next;
    }while (temp != NULL);
    printf("\n");
    return;
}
