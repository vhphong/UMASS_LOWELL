#ifndef FERRY_H
#define FERRY_H
#include "status.h"

typedef void* QUEUE;

QUEUE queue_init_default(void);

Status queue_enqueue(QUEUE hQueue, int item);

Status queue_dequeue(QUEUE hQueue);

Boolean queue_empty(QUEUE hQueue);

int queue_front(QUEUE hQueue, Status* pStatus);

void queue_destroy(QUEUE *phQueue);

void queue_print(QUEUE hQueue);

#endif