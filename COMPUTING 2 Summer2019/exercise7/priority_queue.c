/**********************************************************************
Program:  exercise 7
Author:  Phong Vo
Date:    08/01/2019
Time spent:  3 days
Purpose: to learn more about the roles of priority queue
Rev. 1: 
	Commented out the if statement at line #156 because it is always TRUE.
	Initialized retVal = 0 in function priority_queue_front.
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

struct item{
	int priority;
	int data;
};
typedef struct item Item;

struct priority_queue{
	Item* heap;
	int size;
	int capacity;
};
typedef struct priority_queue Priority_Queue;

//Precondition: Creates an empty priority queue that can store integer data items 
// with different integer priority. Higher
// integer values indicate higher priority in the queue. For example, consider the 
// priority and the data value to be key-value pairs where the priority is the key
// and the data is the value. The queue could hold 21,10 and 35, 5 so that the
// first item to be removed from the queue would be the data value 5 because 
// it has higher priority (35) than the data value 10 which only has (21).
//Postcondition: Returns the handle to an empty priority queue.
PRIORITY_QUEUE priority_queue_init_default(void){
	Priority_Queue* pQueue = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	if (!pQueue){
		printf("Failed to allocate memory. \n");
		return pQueue;
	}
	pQueue->size = 0;
	pQueue->capacity = 4;
	pQueue->heap = (Item*)malloc(sizeof(Item) * pQueue->capacity);
	if (pQueue->heap == NULL){
		free(pQueue);
		pQueue = NULL;
	}
	return pQueue;
}

//Precondition: hQueue is a handle to a valid priority queue opaque object. 
// Higher priority_level values indicate higher priority in the queue.
// data_item is simply a value we are storing in the queue.
//Postcondition: returns SUCCESS if the item was successfully added to the queue
// and FAILURE otherwise.
Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item){
	Priority_Queue* pQueue = (Priority_Queue*) hQueue;
	int parentIndex, insertionIndex;
	
	if (pQueue->size >= pQueue->capacity){
		Item* temp = (Item*)malloc(sizeof(Item) * pQueue->capacity * 2);
		if (!temp){
			return FAILURE;
		}
		
		for (int i = 0; i < pQueue->size; ++i){
			temp[i] = pQueue->heap[i];
		}
		free(pQueue->heap);
		pQueue->heap = temp;
		pQueue->capacity *= 2;
	}
	pQueue->size++;
	insertionIndex = pQueue->size - 1;
	parentIndex = (insertionIndex) / 2;
	
	while ((insertionIndex > 0) && (priority_level < pQueue->heap[parentIndex].priority)){
		pQueue->heap[insertionIndex] = pQueue->heap[parentIndex];
		insertionIndex = parentIndex;
		parentIndex = (insertionIndex - 1) / 2;
	}
	pQueue->heap[insertionIndex].data = data_item;
	pQueue->heap[insertionIndex].priority = priority_level;
	
	return SUCCESS;
}

//Precondition: hQueue is a handle to a valid priority queue opaque object. 
//Postcondition: returns SUCCESS if the highest priority item was removed from the queue 
// and FAILURE if the queue was empty.
Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_Queue* pQueue = (Priority_Queue*)hQueue;
	Item* temp;
	int parentIdx = 0;
	int lChildIdx = 1;
	int rChildIdx = 2;
	int qSize, currentIdx;

	if (pQueue->size == 0)	{
		printf("Queue is empty.\n");
		return FAILURE;
	}
	if (pQueue->size == 1){
		pQueue->size--;
	}
	else{
		do{
			if ((rChildIdx > (pQueue->size - 1)) || (pQueue->heap[lChildIdx].priority < pQueue->heap[rChildIdx].priority)){
				pQueue->heap[parentIdx] = pQueue->heap[lChildIdx];
				parentIdx = lChildIdx;
			}
			else{
				pQueue->heap[parentIdx] = pQueue->heap[rChildIdx];
				parentIdx = rChildIdx;
			}
			lChildIdx = parentIdx * 2 + 1;
			rChildIdx = parentIdx * 2 + 2;
		} while (lChildIdx <= pQueue->size - 1);

		qSize = pQueue->size;
		currentIdx = parentIdx + 1;
		while (currentIdx != qSize){
			pQueue->size = currentIdx - 1;
			priority_queue_insert(hQueue, pQueue->heap[currentIdx].priority, pQueue->heap[currentIdx].data);
			currentIdx++;
		}
		pQueue->size = qSize - 1;

		if (pQueue->size < pQueue->capacity / 2 && pQueue->size >= 4){
			temp = (Item*)malloc(sizeof(Item) * (pQueue->capacity / 2));
			if (temp == NULL){
				return FAILURE;
			}
			for (int i = 0; i < pQueue->size; i++){
				temp[i] = pQueue->heap[i];
			}
			free(pQueue->heap);
			pQueue->heap = temp;
			pQueue->capacity = pQueue->capacity / 2;
		}
	}
	return SUCCESS;
}


//Precondition: hQueue is a handle to a valid priority queue opaque object. 
//Postcondition: returns a copy of the data value for the
// highest priority item in the queue. Sets status to SUCCESS if there is
// at least one item in the queue and FAILURE otherwise. If status is
// passed in as NULL then the status value is ignored for this run of the
// function.
int priority_queue_front(PRIORITY_QUEUE hQueue, Status* status){
	Priority_Queue* pQueue = (Priority_Queue*) hQueue;
	
	int retVal = 0;
	// if (status != NULL){
		if (priority_queue_is_empty(hQueue) == TRUE){
			*status = FAILURE;
			retVal = -1;
		}
		else {
			*status = SUCCESS;
			retVal = pQueue->heap[0].data;
		}
	// }
	return retVal;
}

//Precondition: hQueue is a handle to a valid priority queue opaque object. 
//Postcondition: returns TRUE if the priority_queue is empty and FALSE otherwise.
Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue){
	Priority_Queue* pQueue = (Priority_Queue*) hQueue;
	if (pQueue->size > 0){	// if pQueue is greater than 0
		return FALSE;
	}
	return TRUE;
}

//Precondition: phQueue is a pointer to the handle of a valid priority queue opaque object.
//Postcondition: The opaque object will be free'd from memory and the handle pointed to
// by phQueue will be set to NULL.
void priority_queue_destroy(PRIORITY_QUEUE* phQueue){
	Priority_Queue* pQueue = (Priority_Queue*) phQueue;
	if (pQueue != NULL){
		free(pQueue->heap);
		free(pQueue);
		*phQueue = NULL;
	}
}
