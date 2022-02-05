#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include <string.h>


pLinkedList linkedlistInitDefault()
{
  pLinkedList list = malloc(sizeof(LinkedList));
  list->front = NULL;
  list->iterator = NULL;
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
	  list->front->data = item;
	  list->size++;
	}
    }
  else
    {
      Node_Ptr current = list->front;
      while(current->next != NULL)
	{
	  current = current->next;
	}
      current->next = malloc(sizeof(Node));
      if(current->next!=NULL)
	{
	  current->next->data = item;
	  current->next->next = NULL;
	  list->size++;
	}
      
    }
  
}


void linkedlistDestroy(pLinkedList *list)
{
  if((*list) != NULL)
    {
      if((*list)->front == NULL)
	{
	  free((*list));
	  (*list) = NULL;
	}
      else
	{
	  printf("looping to delete all nodes\n");
	  Node_Ptr current = (*list)->front;
	  Node_Ptr next = (*list)->front;
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


void linkedlist_display(pLinkedList list) {
	
	Node_Ptr current;
	Node_Ptr currentNext;

	current = list->front;

	while(current != NULL) {
		currentNext = current->next;
		printf("%s\t", current->data);
		current = currentNext;
	}

}


void selection_sort(pLinkedList list) {
	Node_Ptr current;
	Node_Ptr smallest;
	  // checks if the linkedlist is empty
	if (list == NULL) {
		printf("List is empty\n");
		exit(1);
		}
	else if (list->size == 0 || list->size == 1){
		printf("Cant compare 0 or 1 string!!\n");
		exit(1);
		}
	else {

		list->iterator = list->front;
		current = list->front->next;
		smallest = list->front;

		while (list->iterator->next != NULL) 
		{

			while (current != NULL) {
			// assigns the smallest to a variable
			if (less(smallest->data, current->data) > 0) {
				smallest = current;
				}
				//loop through the linked list			
				current = current->next;
			}

			swap(list->iterator, smallest);
			list->iterator = list->iterator->next;
			smallest = list->iterator;
			current = list->iterator->next;
		}
	}
}



void swap(Node_Ptr left, Node_Ptr right) {
	Item temp = left->data;
	left->data = right->data;
	right->data = temp;
}

int less(Item left, Item right) {
	if (left == NULL || right== NULL) {
		printf("error string is null");
		exit(1);
	}
	else {
		return strcmp(left, right);
	}
}



void linkedlistScanInit(pLinkedList list)
{
	Item arr;
	char arr_1[100];

	int length, j, size,   i = 0;
	char word;
	printf("How many string do you want to compare?\n");
	scanf("%d", &size);

	for (j = 0; j < size; j++){
		printf("Enter your string #%d:",j+1);
		scanf(" %c", &word);
		while (word != '\n')
		{
			arr_1[i] = word;
			i++;
			scanf("%c", &word);
		}
		length = i;
		arr = (char*)malloc(sizeof(char)*length);
		for (i = 0; i < length; i++)
		{
		arr[i] = arr_1[i];
		}
		arr[i] = '\0';
		linkedlistAddNodeBack(list, arr);
		i = 0;
	}

	list->size = size;
}

