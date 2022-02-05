/**********************************************************************
 Program: Daily 7
 Author: Viet Tran Quoc Hoang
 Date: 2/27/2016
 Time spent: 2 days
 Purpose: Implementation of stack using linked lists based on parentheses problem
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "status.h"
int main(int argc, const char * argv[]) {
    
    int counter = 0,i;
    scanf("%d\n",&counter);
    //printf("%d\n",counter);
     Status string_status = SUCCESS;
    for (i = 0; i <counter; i++) {
        char ch;
        STACK hStack = NULL;
        hStack = stack_init_default();
        do{
            ch = fgetc(stdin);
            if (ch == '\n') {
                break;
            }
            //printf("%c",ch);
            switch (ch) {
                case '(': case '[': case '{':
                    hStack->push(hStack,ch);
                    break;
                case ')':
                    if(hStack->pop_item(hStack,'(')== FAILURE){
                        string_status = FAILURE;
                    }
                    break;
                case ']':
                    if(hStack->pop_item(hStack,'[')== FAILURE){
                        string_status = FAILURE;
                    }
                    break;
                case '}':
                    if(hStack->pop_item(hStack,'{')== FAILURE){
                        string_status = FAILURE;
                    }
                    break;
            }
            if (string_status == FAILURE) {
                while (ch != '\n') {
                    ch = fgetc(stdin);
                }
                break;
            }
        }while (ch != EOF);
            //printf("    stack content: ");hStack->print(hStack);
            if (string_status != FAILURE ) {
                if (hStack->empty(hStack)) {
                    printf("Yes\n");
                }
                else{
                    printf("No\n");//, stack is not empty
                }
            }
            else{
                printf("No\n");//, string is not valid
            }
            hStack->destroy(&hStack);
            string_status = SUCCESS;
    }
    return 0;
}