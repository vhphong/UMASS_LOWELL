#pragma once
#include <stdlib.h>
#include "status.h"

typedef void* QUEUE;

//init
QUEUE queue_init_default(void);

//enqueue
//Precondition: handle hQueue to a valid queue object
//Postcond: return SUCCESS if add item, FAILED otherwise
Status queue_enqueue(QUEUE hQueue, int item);

//dequeue
Status queue_dequeue(QUEUE hQueue);

//if empty
Boolean queue_empty(QUEUE hQueue);
int queue_head(QUEUE hQueue, Status* pStatus);
void queue_print(hQueue);
//destroy
void queue_destroy(QUEUE* phQueue);