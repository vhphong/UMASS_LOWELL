/**********************************************************************
Program: Priority Queue
Author: Hoang Do
Date: 12/3/2017
Time spent: 2 hours
Purpose: Create a priority queue 
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct element
{
	int priority;
	int data;
};
typedef struct element Element;

struct priority_queue
{
	Element *heap;
	int size;
	int capacity;
};
typedef struct priority_queue Priority_Queue;

PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_Queue* pQueue;
	pQueue = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	if (pQueue != NULL)
	{
		pQueue->capacity = 4;
		pQueue->size = 0;
		pQueue->heap = (Element*)malloc(sizeof(Element)*pQueue->capacity);
		if (pQueue->heap == NULL)
		{
			free(pQueue);
			pQueue = NULL;
		}
	}
	return pQueue;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;
	Element* temp;
	int i;
	int item_index, parent_index;

	if (pQueue->size >= pQueue->capacity)
	{
		temp = (Element*)malloc(sizeof(Element)*pQueue->capacity * 2);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pQueue->size; i++)
		{
			temp[i] = pQueue->heap[i];
		}
		free(pQueue->heap);
		pQueue->heap = temp;
		pQueue->capacity *= 2;
	}
	pQueue->size++;
	item_index = pQueue->size - 1;
	parent_index = (item_index - 1) / 2;
	while ((item_index > 0) && (priority_level < pQueue->heap[parent_index].priority))
	{
		pQueue->heap[item_index] = pQueue->heap[parent_index];
		item_index = parent_index;
		parent_index = (item_index - 1) / 2;
	}
	pQueue->heap[item_index].data = data_item;
	pQueue->heap[item_index].priority = priority_level;
}

Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;
	Element* temp;
	int parent_index = 0;
	int left_child_index = 1;
	int right_child_index = 2;
	int i, size, current;

	if (pQueue->size == 0)
	{
		printf("Queue is empty.\n");
		return FAILURE;
	}
	if (pQueue->size == 1)
	{
		pQueue->size--;
	}
	else
	{
		do
		{
			if ((right_child_index > (pQueue->size - 1)) || (pQueue->heap[left_child_index].priority < pQueue->heap[right_child_index].priority))
			{
				pQueue->heap[parent_index] = pQueue->heap[left_child_index];
				parent_index = left_child_index;
			}
			else
			{
				pQueue->heap[parent_index] = pQueue->heap[right_child_index];
				parent_index = right_child_index;
			}
			left_child_index = parent_index * 2 + 1;
			right_child_index = parent_index * 2 + 2;
		} while (left_child_index <= pQueue->size - 1);

		size = pQueue->size;
		current = parent_index + 1;
		while (current != size)
		{
			pQueue->size = current - 1;
			priority_queue_insert(hQueue, pQueue->heap[current].priority, pQueue->heap[current].data);
			current++;
		}

		pQueue->size = size - 1;

		if (pQueue->size < pQueue->capacity / 2 && pQueue->size >= 4)
		{
			temp = (Element*)malloc(sizeof(Element) * (pQueue->capacity / 2));
			if (temp == NULL)
			{
				return FAILURE;
			}
			for (i = 0; i < pQueue->size; i++)
			{
				temp[i] = pQueue->heap[i];
			}
			free(pQueue->heap);
			pQueue->heap = temp;
			pQueue->capacity = pQueue->capacity / 2;
		}
	}
	return SUCCESS;
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* status)
{
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;

	if (priority_queue_is_empty(hQueue))
	{
		if (status != NULL)
		{
			*status = FAILURE;
		}
		return -1;
	}

	if (status != NULL)
	{
		*status = SUCCESS;
	}
	return pQueue->heap[0].data;
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;
	if (pQueue->size != 0)
	{
		return FALSE;
	}
	return TRUE;
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
	Priority_Queue* pQueue = (Priority_Queue*)*phQueue;
	if (pQueue != NULL)
	{
		free(pQueue->heap);
		free(pQueue);
		*phQueue = NULL;
	}
}
