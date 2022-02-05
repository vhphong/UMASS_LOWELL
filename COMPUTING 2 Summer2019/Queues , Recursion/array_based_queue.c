#include <stdlib.h>
#include "queue.h"

//known type
struct queue
{
	int size; //trusted
	int capacity; //trusted
	int* data; //trusted
	int front; //not trusted unless the queue is non-empty
	int rear; //not trusted unless the queue is non-full
};

typedef struct queue Queue;

QUEUE queue_constructor(int capacity)
{
	Queue* pQueue;

	pQueue = (Queue*) malloc(sizeof(Queue));
	if (pQueue != NULL)
	{
		pQueue->capacity = capacity;
		pQueue->size = 0;
		pQueue->front = 0;
		pQueue->rear = 0;
		pQueue->data = (int*) malloc(sizeof(int) * pQueue->capacity);
		if (pQueue->data == NULL)
		{
			free(pQueue);
			pQueue = NULL;
		}
	}
	return (QUEUE) pQueue;
}

Status queue_enqueue(QUEUE hQueue, int item)
{
	Queue* pQueue = (Queue*) hQueue;
	int* temp;
	int i;

	if (pQueue->size >= pQueue->capacity) //it is full (there is no room) so fix it
	{
		temp = (int*) malloc(sizeof(int) * pQueue->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		//copy the old info into temp
		for (i = 0; i < pQueue->size; i++)
		{
			temp[i] = pQueue->data[(pQueue->front + i) % pQueue->capacity];
		}
		free(pQueue->data);
		pQueue->data = temp;
		pQueue->front = 0;
		pQueue->rear = pQueue->size;
		pQueue->capacity *= 2;
	}
	pQueue->data[pQueue->rear] = item;
	pQueue->size++;
	pQueue->rear = (pQueue->rear + 1) % pQueue->capacity;

	return SUCCESS;
}

Status queue_dequeue(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;

	if (queue_empty(hQueue))
	{
		return FAILURE;
	}
	pQueue->front = (pQueue->front + 1) % pQueue->capacity;
	pQueue->size--;
	return SUCCESS;
}

Boolean queue_empty(QUEUE hQueue)
{
	Queue* pQueue = (Queue*)hQueue;
	if (pQueue->size == 0)
	{
		return TRUE;
	}
	return FALSE;
}

int queue_front(QUEUE hQueue, Status* pStatus)
{
	Queue* pQueue = (Queue*)hQueue;

	if (queue_empty(hQueue)) //the queue is empty
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
		}
		return -8887888;
	}
	if (pStatus != NULL)
	{
		*pStatus = SUCCESS;
	}
	return pQueue->data[pQueue->front];	
}

void queue_destroy(QUEUE* phQueue)
{
	Queue* pQueue = (Queue*)*phQueue;

	free(pQueue->data);
	free(pQueue);
	*phQueue = NULL;

	return;
}