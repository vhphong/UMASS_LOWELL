/**********************************************************************
 Program: Daily 7
 Author: Viet Tran Quoc Hoang
 Date: 2/27/2016
 Time spent: 2 days
 Purpose: Implementation of stack using linked lists based on parentheses problem
 ***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

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

STACK stack_init_default(void);
Status stack_push(STACK hStack,char item);
Status stack_pop_top(STACK hStack);
Status stack_pop_item(STACK hStack,char item);
char stack_top(STACK hStack,Status* pStatus);
Boolean stack_empty(STACK hStack);
void stack_destroy(STACK* phStack);
void stack_print(STACK hStack);

int main(int argc, const char * argv[]) {
    int counter=0,i;
    scanf("%d\n",&counter);
    printf("%d\n",counter);
    for (i = 0; i < counter; i++) {
        char ch;
        Status string_status= SUCCESS;
        STACK hStack = NULL;
        hStack = stack_init_default();
        Boolean valid_status = FALSE;
        do{
            ch = fgetc(stdin);
            if (ch == '\n') {
              //  printf("break by endl\n");
                break;
                }
            //printf("%d",i);printf("%c",ch);
            switch (ch) {
                case '(': case '{': case '[':
                    hStack->push(hStack,ch);
                    valid_status = TRUE;
                break;
            
                case ')':
                    if (hStack->pop_item(hStack,'(')==FAILURE){//if cant find matching item to pop,
                        string_status = FAILURE;
                    }
                    valid_status = TRUE;
                break;
                
                case '}':
                    if (hStack->pop_item(hStack,'{')==FAILURE){
                        string_status = FAILURE;
                    }
                    valid_status = TRUE;
                break;
                
                case ']':
                    if (hStack->pop_item(hStack,'[')==FAILURE) {
                        string_status = FAILURE;
                    }
                    valid_status = TRUE;
                break;
                }
            if (string_status == FAILURE) {
               // printf("break by fail status\n");
                break;
            }
        }while (ch != EOF );
        //printf("Stack content:");hStack->print(hStack);
        
        if (!valid_status){
            i--;//preventing checking empty stack returned from endl
            hStack->destroy(&hStack);
            continue;
        }
    
         if (hStack->empty(hStack)) {
                //printf("\n");
                if (string_status == SUCCESS) {
                    printf("Yes\n");
                }
                else{
                    printf("No\n");//from empty stack
                }
            }
            else{
                //printf("\n");
                printf("No\n"); //from non-empty stack
            }
      
        hStack->destroy(&hStack);
    }
    
    return 0;
}

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
        printf("empty stack\n");
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
        //printf("stack is already empty\n");
        return FAILURE;
    }
    Node* current = pStack->head;
    Node* prev = NULL;
    while (current != NULL){
        if (current->data == item) {
            if (prev == NULL) {//if beginning of list, pop top
                pStack->head  = current->next;//can also use pop top function hStack->pop_top(hStack)
            }
            else{
                prev->next = current->next;//if somewhere else, remove node and reconnect list
            }
            free(current);
            return SUCCESS;
        }
        prev = current;
        current = current->next;
    }
    //printf("unable to pop item %c\n",item);
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

