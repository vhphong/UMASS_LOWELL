/***********************************************************
Author: Phong Vo
Date: 04/10/2018
Effort: 10 hrs
Purpose: daily8
Interface proposal: 
***********************************************************/

#include<stdio.h>
#include<stdlib.h>

// structure to construct a node
struct Node
{
	int priority;
	int info;
	struct Node *next;
}*start = NULL, *q, *temp, *new;

typedef struct Node node;

// method to insert an element with its priority
void q_insert()
{
	int ele, prio;
	new = (node *)malloc(sizeof(node));
	printf("Enter an element to insert :\t");
	scanf_s("%d", &ele);
	printf("Enter its priority :\t");
	scanf_s("%d", &prio);

	new->info = ele;
	new->priority = prio;
	new->next = NULL;
	if (start == NULL)
	{
		start = new;
	}
	else if (start != NULL && prio <= start->priority)
	{
		new->next = start;
		start = new;
	}
	else
	{
		q = start;
		while (q->next != NULL && q->next->priority <= prio)
		{
			q = q->next;
		}
		new->next = q->next;
		q->next = new;
	}
}

// method to delete an element
void q_del()
{
	if (start == NULL)
	{
		printf("\nError: Queue is underflow\n");
	}
	else
	{
		new = start;
		printf("\nThe deleted element is: %d\n", new->info);
		start = start->next;
	}
}

// to display the queue
void q_show()
{
	temp = start;
	if (start == NULL)
		printf("Queue is empty\n");
	else
	{
		printf("The queue is:\n");
		if (temp != NULL)
			for (temp = start; temp != NULL; temp = temp->next)
			{
				printf("\n%d priority =%d\n", temp->info, temp->priority);
			}
	}
}