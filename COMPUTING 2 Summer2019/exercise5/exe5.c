/**********************************************************************
Program:  Exercise 5 - Put a linked list in reversed order of nodes
Author:  Phong Vo
Date: 07/25/2019   
Time spent: 30 minutes
Purpose: The purpose of this program is getting learned more on linked list.
         Study how to manipulate nodes of an linked list.
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
// typedef Node* pMyNode;

// declare your function here.
Node* reversedList(Node* pHead);

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
    head = reversedList(head);

	//print the reversed list.
	temp = head;
	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->next;
	}

	return 0;
}

//Define your function here
Node* reversedList(Node* pHead){
    Node *temp_prev, *temp_cur, *temp_next;
    temp_prev = NULL;
    temp_cur = pHead;
    while (temp_cur !=NULL){
        temp_next = temp_cur->next;
        temp_cur->next = temp_prev;
        temp_prev = temp_cur;
        temp_cur = temp_next;
    }
    pHead = temp_prev;
    return pHead;
}