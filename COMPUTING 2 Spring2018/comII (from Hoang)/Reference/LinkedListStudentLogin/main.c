//****************************************
/** 
//Program: Account management system
//Author : Viet Tran Quoc Hoang 
//Date: 11/14/2015
//Time spent: 12 hours 
//Purpose: Allow user to add in accounts,log in/out,
delete account,find account by username
print out all created accounts using linked lists
Features: unique username,status management
(if already logged in/out,cant log in/out again)
Program will attempt to free memories once the program terminates,
deleting all nodes inside the linked lists
*/
//****************************************//
#include <stdio.h>
#include <stdlib.h>
#include "linkedListSt.h"
#include <string.h>
int main()
{
  char memberName[30];
  char userName[30];
  char searchString[30];
  char cont;
  pLinkedList list = linkedlistInitDefault();
  int choice;
  printf("\nPlease enter numbers 0-6 for the following options:\n1)Add user\n2)Print a list of all accounts\n3)Find an account\n4)Log in to your account\n5)Log out of your account\n6)Delete an account\n0)Quit\n");
  printDivider();
  scanf("%d",&choice);
    do {
  switch(choice)
    {case 1:
      	printf("%s","Enter the name of the user(no spaces):");
      	scanf("%s",memberName);
      	printf("%s","Enter the username for the account:");
      	scanf("%s",userName);
      	list =create(userName,memberName,list);
        printList(list);
     break;

    case 2:
        printList(list);   
    break;

    case 3:
      printf("%s","Enter the username of the account you want to look for:");
      scanf("%s",searchString);
      searchbyUserName(searchString,list);
    break;  

    case 4:
      printf("%s","Enter the username of the account to be logged in:");
      scanf("%s",searchString);
      login(&list,searchString);
      printList(list);
    break;

    case 5:
      printf("%s","Enter the username of the account to be logged out:");
      scanf("%s",searchString);
      logout(&list,searchString);
      printList(list);
    break;

    case 6:
      printf("%s","Enter the username of the account to be deleted:");
      scanf("%s",searchString);
      deleteUser(&list,searchString);
      printList(list);
    break;

    case 0:
      deleteAll(list);
      printf("Program terminating\n"); 
      return 0;
    break;   

    }
   printf("Enter m to display the option menu again or q to quit:");
   scanf(" %c",&cont);
   switch(cont){
    case 'm':
    case 'M':
      printf("\nPlease enter numbers 0-6 for the following options:\n1)Add user\n2)Print a list of all accounts\n3)Find an account\n4)Log in to your account\n5)Log out of your account\n6)Delete an account\n0)Quit\n");
      printDivider();
      scanf("%d",&choice);
    break;

    case 'q': 
    case 'Q':
      deleteAll(list);
      printf("Program terminating\n"); 
      return 0;
    break;

   } 
  }while (choice!=9);
printf("Please enter something\n");
}
//function:create,login,logout,search,print(display username,membername,status:online or offline,remove user)

