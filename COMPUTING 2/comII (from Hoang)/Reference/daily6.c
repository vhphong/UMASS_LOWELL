/**********************************************************************
Program: <Daily 6>
Author: <Rushabh Doshi>
Date: <8-2-2016>
Time spent: <20 minutes>
Purpose: The purpose of this program is to reverse a linked list
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node, *Node_Ptr;
typedef int Item;



struct node
{
	Item data;
	Node_Ptr next;
};
//declare your function here. 
Node_Ptr Reverse(Node_Ptr* head);



int main(int argc, char* argv[])
{
	Node_Ptr head = NULL;
	int i;
	Node_Ptr temp; //set up a test list with values 9->8->7->...->0 
	for (i = 0; i < 10; i++)
	{
		temp = (Node_Ptr)malloc(sizeof(Node));
		if (temp == NULL)
		{
			printf("out of memory\n");
			exit(1);
		}
		temp->data = i;
		temp->next = head;
		head = temp;
	}

	//call your function to reverse the list (should work for any list given the head node). 
	head =  Reverse(head);

	//print the reversed list. 
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}

	
	return 0;
}


Node_Ptr Reverse(Node_Ptr* head)
{
	Node *temp, *prev, *current, *next;
	current = head;
	prev = NULL;
	while (current != NULL) {
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;	
	}
	head = prev;
	return head;

}