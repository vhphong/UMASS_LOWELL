#include <stdio.h>
#include <stdlib.h>
#include "ferry.h"

struct node;
typedef struct node Node;
struct node
{
	int data;
	Node* next;
};

struct queue
{
	Node *head;
	Node *tail;
};

typedef struct queue Queue;
typedef Queue* Queueptr;

QUEUE queue_init_default(void)
{
	Queueptr pQueue;
	pQueue = (Queueptr)malloc(sizeof(Queue));
	if(pQueue != NULL)
	{
		pQueue->head = NULL;
		pQueue->tail = NULL;
	}
	return pQueue;
}

Status queue_enqueue(QUEUE hQueue, int item)
{
	Queueptr pQueue = (Queueptr)hQueue;
	Node *temp;
	temp = (Node*)malloc(sizeof(Node));
	if(temp == NULL)
	{
		return FAILURE;
	}
	temp->data = item;
	temp->next = NULL;
	if(pQueue->head == NULL)
	{
		pQueue->head = temp;
		pQueue->tail = temp;
	}
	else
	{
		pQueue->tail->next = temp;
		pQueue->tail = temp;
	}
	return SUCCESS;
}

Status queue_dequeue(QUEUE hQueue)
{
	Queueptr pQueue = (Queueptr)hQueue;	
	if(queue_empty(hQueue))
	{
		return FAILURE;
	}
	Node *temp;
	temp = pQueue->head;
	pQueue->head = pQueue->head->next;
	if(pQueue->head == NULL)
	{
		pQueue->tail = NULL;
	}
	free(temp);
	return SUCCESS;
}

Boolean queue_empty(QUEUE hQueue)
{
	Queueptr pQueue = (Queueptr)hQueue;
	return (Boolean)(pQueue->head == NULL);
}

int queue_front(QUEUE hQueue, Status* pStatus)
{
	Queueptr pQueue = (Queueptr)hQueue;
	if (pQueue == NULL)
	{
		*pStatus = FAILURE;
		return -1;
	}
	if (pQueue->head == NULL)
	{
		*pStatus = FAILURE;
		return -1;
	}
	int hold = pQueue->head->data;
	*pStatus = SUCCESS;
	return hold;
}

void queue_destroy(QUEUE *phQueue)
{
	Queueptr pQueue = (Queueptr) *phQueue;
	while(pQueue->head != NULL)
	{
		Node *temp = pQueue->head;
		pQueue->head = pQueue->head->next;
		free(temp);
	}
	free(*phQueue);
	*phQueue = NULL;
	return;
}

void queue_print(QUEUE hQueue)
{
    Queueptr pQueue = (Queueptr) hQueue;
    if (pQueue->head == NULL) 
	{
        printf("Queue is empty\n");
        return;
    }
    Node *temp = pQueue->head;
    while (temp != NULL) 
	{
        printf("%d",temp->data);
        printf(" ");
        temp = temp->next;
    }
    printf("\n");
    return;
}