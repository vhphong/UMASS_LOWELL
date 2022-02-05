/******************************************************************************
Author: Hoang Do
Date: 10/4/2017
Effort: 20 mins
Purpose: Learn how to work with the link list, make a reverse function for a link list
******************************************************************************/

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
Node* reverse_list(Node* head);

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
	head = reverse_list(head);

	//print the reversed list.
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp-> data);
		temp = temp -> next;
	}

	return 0;
}

//Define your function here
Node* reverse_list(Node* head)
{
    struct node *temp, *temp1, *var;
    temp = head;
    var = NULL;
    while(temp != NULL)
    {
         temp1 = var;
         var = temp;
         temp = temp -> next;
         var -> next = temp1;
    }
    head = var;
    return head;
}
