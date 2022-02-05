
/**********************************************************************
 Program: Ferry Queue
 Author: Viet Tran Quoc Hoang
 Date: 3/4/2016
 Time spent: 2 days
 Purpose: The purpose of this program is to simulate loading and unloading cars of a single lane ferry across a river. There are 2 queues of car on the left and right banks.
 ***********************************************************************/
#ifndef linked_queue_h
#define linked_queue_h
#include "status.h"

struct public_queue;
typedef struct public_queue Public_queue;
typedef Public_queue* QUEUE;

struct public_queue{
    Status(*enqueue)(QUEUE hQueue, int item);
    Status(*service)(QUEUE hQueue);
    Boolean(*empty)(QUEUE hQueue);
    int(*front)(QUEUE hQueue, Status* pStatus);
    void(*destroy)(QUEUE* phQueue);
    void(*print)(QUEUE hQueue);
};
//init_default
QUEUE queue_init_default(void);

//enqueue
Status queue_enqueue(QUEUE hQueue, int item);

//service
Status queue_service(QUEUE hQueue); //pop front

//empty
Boolean queue_empty(QUEUE hQueue);

//front
int queue_front(QUEUE hQueue, Status* pStatus);

//destroy
void queue_destroy(QUEUE* phQueue);

//print
void queue_print(QUEUE hQueue);
#endif /* linked_queue_h */
