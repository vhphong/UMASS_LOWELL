/**********************************************************************
Program:  daily6.c
Author:  Phong Vo
Date:    02/10/2018
Time spent:  3hrs
Purpose:     The purpose of this program is to manipulate linked list
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

//declare your function here.

Node * reverse(Node * list);
void print(Node *list);

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
	temp = head;
	//printing list
	print(temp);

	//call your function to reverse the list (should work for any list given the head node).
	temp = reverse(head);

	//print the reversed list.

	// temp = head;
	print(temp);

	return 0;

}

void print(Node *list) {
	Node *temp = list;
	while (temp != NULL)
	{
		printf("%d->", temp->data);
		temp = temp->next;
	}
	printf("NULL \n");
}

Node * reverse(Node * list)
{
	Node * temp;
	Node * previous = NULL;
	Node *current = list;
	while (current != NULL) {
		temp = current->next;
		current->next = previous;
		previous = current;
		current = temp;
	}
	return previous;
}