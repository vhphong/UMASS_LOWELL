#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct queue {
	int size;
	int capacity;
	int* data;
	int head;
	int tail;
};

typedef struct queue Queue;

QUEUE queue_init_default(void) {
	Queue* pQueue;
	pQueue = (Queue*)malloc(sizeof(Queue));
	if (pQueue != NULL) {
		pQueue->size = 0;
		pQueue->capacity = 1;
		pQueue->head = 0;
		pQueue->tail = 0;
		pQueue->data = (int*)malloc(sizeof(int)*pQueue->capacity);
		if (pQueue->data == NULL) {
			free(pQueue);
			pQueue = NULL;
		}
	}
	return pQueue;
}
Status queue_enqueue(QUEUE hQueue, int item) {
	Queue* pQueue = (Queue*)hQueue;
	int* temp;
	int i;
	if (pQueue->size >= pQueue->capacity) {
		temp = (int*)malloc(sizeof(int) * 2 * pQueue->capacity);
		if (temp == NULL) {
			return FAILURE;
		}
		for (i = 0; i < pQueue->size; i++) {
			temp[i] = pQueue->data[(pQueue->head + i) % pQueue->capacity];
		}
		pQueue->head = 0;
		pQueue->tail = pQueue->size - 1;
		free(pQueue->data);
		pQueue->data = temp;
		pQueue->capacity *= 2;
	}
	pQueue->tail = (pQueue->tail + 1) % pQueue->capacity;
	pQueue->data[pQueue->tail] = item;
	pQueue->size++;
	printf("size = %d capacity = %d head = %d tail = %d\n", pQueue->size, pQueue->capacity,
		pQueue->head, pQueue->tail);
	return SUCCESS;
}
Status queue_dequeue(QUEUE hQueue) {
	Queue* pQueue = (Queue*)hQueue;
	if (pQueue->size == 0) {
		return FAILURE;
	}
	pQueue->head = (pQueue->head + 1)%pQueue->capacity;
	pQueue->size--;
	return SUCCESS;
}

int queue_head(QUEUE hQueue, Status* pStatus) {
	Queue* pQueue = (Queue*)hQueue;
	//printf("in queue_head pQueue->size = %d pQueue->head=%d\n", pQueue->size, pQueue->head);
	if (pQueue->size == 0) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		printf("*pStatus =%d\n", *pStatus);
		return INT_MIN;
	}
	else {
		*pStatus = SUCCESS;
		return pQueue->data[pQueue->head];
	}
}
void queue_print(QUEUE hQueue) {
	Queue* pQueue = (Queue*)hQueue;
	int i;
	if (pQueue->size == 0)
		printf("Queue is empty\n");
	else {
		//for (i = pQueue->head; i != ((pQueue->tail)+1) % pQueue->capacity; (i++) % pQueue->capacity)
		for (i = 0; i < pQueue->size; i++) {
			printf("i=%d  item=%d\n", 
				(pQueue->head + i) % pQueue->capacity, 
				pQueue->data[(pQueue->head + i) % pQueue->capacity]);
		}
	}
}

void queue_destroy(QUEUE* phQueue) {
	Queue* pQueue = (Queue*)*phQueue;
	free(pQueue->data);
	free(pQueue);
	*phQueue = NULL;
}
