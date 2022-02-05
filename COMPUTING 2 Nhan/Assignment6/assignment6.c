/**********************************************************************
Program: Reverse Node
Author: Nhan Tran
Date: 10-05-2017
Time spent: 2 hours
Purpose: The purpose of this program is to understand linked list
***********************************************************************/
#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
};
typedef Node* Node_Ptr;
//declare your function here.
Node_Ptr Reverse(Node_Ptr head);

int main(int argc, char* argv[])
{
	Node* head = NULL;
	int i;
	Node* temp;

	//set up a test list with values 9->8->7->...->0
	for (i = 0; i < 10; i++)
	{
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
		{
			printf("out of memory?\n");
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

//Define your function here1
Node_Ptr Reverse(Node_Ptr head)
{
	Node *prev, *current, *next;
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