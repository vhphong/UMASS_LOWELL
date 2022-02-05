#include <stdio.h>
#include <stdlib.h>
#include "linkedListSt.h"
#include <string.h>

pLinkedList linkedlistInitDefault()
{
  pLinkedList list = malloc(sizeof(LinkedList));
  list->front = NULL;
  list->size = 0;
  return list;
}

int linkedlistGetSize(pLinkedList list)
{
  return list->size;
}

void linkedlistAddNodeBack(pLinkedList list, Item item)
{
  if(list->front == NULL)
    {
      list->front = malloc(sizeof(Node));
      if(list->front != NULL)
	{
	  list->front->next = NULL;
	  list->front->item = item;
	  list->size++;
	}
    }
  else
    {
      pNode current = list->front;
      while(current->next != NULL)
	{
	  current = current->next;
	}
      current->next = malloc(sizeof(Node));
      if(current->next!=NULL)
	{
	  current->next->item = item;
	  current->next->next = NULL;
	  list->size++;
	}
      
    }
  
}

void linkedlistDestroy(pLinkedList *list)
{
  if((*list) != NULL)
    {
      printf("list is not null\n");
      if((*list)->front == NULL)
	{
	  free((*list));
	  (*list) = NULL;
	}
      else
	{
	  printf("looping to delete all nodes\n");
	  pNode current = (*list)->front;
	  pNode next = (*list)->front;
	  while(current!=NULL)
	    {
	      printf("I am deleting here\n");
	      next = current->next;
	      free(current);
	      current = next;  
	    }
	  printf("setting the list to null\n");
	  free((*list));
	  (*list) = NULL;
	}
    }

}

pLinkedList create(char* userName,char* memberName,pLinkedList list){
  pNode current = list->front;
  while(current!=NULL){//if list have existing members, check for duplicate name
        if(strcmp(current->item.username,userName)==0){
        printf("The username %s has already been used.Please enter a different username\n",userName);
        printDivider();
        return list;
        }
        else    
        current= current->next;
    }
  Item info;
  info.name=malloc(sizeof(Item)*strlen(memberName));
  info.username=malloc(sizeof(Item)*strlen(userName));
  strcpy(info.name,memberName);
  strcpy(info.username,userName);
  info.s=offline; 
  linkedlistAddNodeBack(list,info);
  return list;
}

Item getMemberAtIndex(pLinkedList list,int index){
  if(index > list->size)
    exit(1);
    int i;
  pNode current = list->front;
  for( i = 0 ; i < index ; i++)
    current = current->next;
  return current->item;
}
  
void printList(pLinkedList list){
  const char* accountstatus[]={"Online","Offline"};
  printf("%-10s%-10s%-10s\n","Username","Name","Status");
  printTableDivider();
   if(list->front == NULL){//empty list check
    printf("No account has been created\n");
   }
   else{
  pNode current = list->front;
  do{
        printf("%-10s%-10s%-10s\n",current->item.username,current->item.name,accountstatus[current->item.s]);
        current= current->next;
        }while (current!=NULL);
    }    
  printDivider();
}

void searchbyUserName(char* searchString,pLinkedList list){
  const char* accountstatus[]={"Online","Offline"};
  printf("%-10s%-10s%-10s\n","Username","Name","Status");  
  printTableDivider();
  if(list->front == NULL){//empty list check
    printf("No account has been created\n");
   }
  else{
  pNode current = list->front;
  do{
        if(strcmp(current->item.username,searchString)==0){
        printf("%-10s%-10s%-10s\n",current->item.username,current->item.name,accountstatus[current->item.s]);
        printDivider();
        return;
        }
        current= current->next;
        }while (current!=NULL);      
  }
  printf("Unable to find account\n");       
  printDivider();
  return;
}

void login(pLinkedList *list,char* searchString){ 
  if((*list)->front == NULL){//empty list check
    return;
   }
   else{
    pNode current = (*list)->front;
  do{   
       if(strcmp(current->item.username,searchString)==0){
        if(current->item.s==online){//check status ,if logged in,prompt user and stop
            printf("Account has already been logged in\n");
            printDivider();
            return;
          }
        else{
            current->item.s=online;
            printDivider();
            return;
          }
        }
        else
        
        current= current->next;
    }while (current!=NULL);
        
    }
  printf("Unable to find account\n");            
  printDivider();
  return;
}

void logout(pLinkedList *list,char* searchString){
  if((*list)->front == NULL){//empty list check
    return;
   }
   else{
    pNode current = (*list)->front;
  do{
        if(strcmp(current->item.username,searchString)==0){
          if(current->item.s==offline){//check status ,if logged out,prompt user and stop
              printf("Account has already been logged out\n");
              printDivider();
              return;
            }
           else{   
              current->item.s=offline;
              printDivider();
              return;
            }
        }
        
        current= current->next;
        }while (current!=NULL);
         
    }    
  printf("Unable to find account\n");       
  printDivider();
  return;
}

void deleteUser(pLinkedList *list,char* searchString){
    if((*list)->front == NULL){//empty list check
    return;
   }
   else{  
    pNode current = (*list)->front; 
    pNode previous = NULL;
  do{
         if(strcmp(current->item.username,searchString)==0){
        //delete node
           if(previous == NULL){//first node deletion
            (*list)->front = current->next;//move beginning node ptr to second node
           }
           else{ 
            previous->next= current->next; //move previous node ptr to next node     
          }    
          free(current);
          printf("Deleted the account of username %s\n",searchString); 
          return; 
        }
        previous = current;
        current= current->next;

    }while (current!=NULL);
    }  
  printf("Unable to find account\n");       
  printDivider();
  return;
 }

void deleteAll(pLinkedList list){
  int i;
  if(list->front!=NULL){//only if list is not empty,clear nodes for member info
  for (i = 0; i < linkedlistGetSize(list); i++) {
        Item member = getMemberAtIndex(list, i);
        free(member.username);          
        free(member.name);//free memory to prevent memory leak
    }
  }  
      linkedlistDestroy(&list);
}

void printDivider()
  {
    printf("-------------------------------------\n");
  }
  
void printTableDivider()
  {
    printf("--------  ----      ------\n");
  }
