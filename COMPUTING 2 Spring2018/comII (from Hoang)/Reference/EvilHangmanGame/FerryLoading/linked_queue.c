
/**********************************************************************
 Program: Ferry Queue
 Author: Viet Tran Quoc Hoang
 Date: 3/4/2016
 Time spent: 2 days
 Purpose: The purpose of this program is to simulate loading and unloading cars of a single lane ferry across a river. There are 2 queues of car on the left and right banks.
 ***********************************************************************/

#include "linked_queue.h"

struct node;
typedef struct node Node;
typedef Node* pNode;

struct node{
    int data;
    pNode next;
};

struct queue{
    Status(*enqueue)(QUEUE hQueue, int item);
    Status(*service)(QUEUE hQueue);
    Boolean(*empty)(QUEUE hQueue);
    int(*front)(QUEUE hQueue, Status* pStatus);
    void(*destroy)(QUEUE* phQueue);
    void(*print)(QUEUE hQueue);
    
    pNode head;
    pNode tail;
};
typedef struct queue Queue;

//init_default
QUEUE queue_init_default(void){
    Queue* pQueue;
    pQueue = (Queue*)malloc(sizeof(Queue));
    if (pQueue) {
        pQueue->enqueue = queue_enqueue;
        pQueue->service = queue_service;
        pQueue->empty = queue_empty;
        pQueue->print = queue_print;
        pQueue->destroy = queue_destroy;
        pQueue->front = queue_front;
        
        pQueue->head = NULL;
        pQueue->tail = NULL;
        return (QUEUE)pQueue;
    }
    return NULL;
}

//enqueue
Status queue_enqueue(QUEUE hQueue, int item){
    Queue* pQueue = (Queue*) hQueue;
    pNode temp = (pNode)malloc(sizeof(Node));
    if (temp == NULL) {
        return FAILURE;
    }
    temp->data = item;
    temp->next = NULL;
    if (pQueue->head == NULL) {
        pQueue->head = temp;
        pQueue->tail = temp;
    }
    else {
        pQueue->tail->next = temp;
        pQueue->tail = temp;
    }
    return SUCCESS;
}

//service//pop front
Status queue_service(QUEUE hQueue){
    Queue* pQueue = (Queue*) hQueue;
    if (pQueue->empty(hQueue)) {
       // printf("Cannot service an empty queue\n");
        return FAILURE;
    }
    pNode head_of_the_queue = pQueue->head;
    pQueue->head = pQueue->head->next;
    if (pQueue->empty(hQueue)) {
        pQueue->tail = NULL;
    }
    free(head_of_the_queue);
    return SUCCESS;
}

//empty
Boolean queue_empty(QUEUE hQueue){
    Queue* pQueue = (Queue*) hQueue;
    return (Boolean)(pQueue->head == NULL);
}
//front
int queue_front(QUEUE hQueue, Status* pStatus){
    Queue* pQueue = (Queue*) hQueue;
    if (pQueue == NULL) {
        *pStatus = FAILURE;
        return -1;
    }
    if (pQueue->head == NULL) {
      //  printf("Queue is empty, cant pop front\n");
        *pStatus = FAILURE;
        return -1;
    }
    int hold = pQueue->head->data;
    *pStatus = SUCCESS;
    return hold;
}

//destroy
void queue_destroy(QUEUE* phQueue){
    Queue* pQueue = (Queue*) *phQueue;
    while (pQueue->head != NULL) {
        pNode temp = pQueue->head;
        pQueue->head = pQueue->head->next;
        free(temp);
    }
    free(*phQueue);
    *phQueue = NULL;
    return;
}

//print
void queue_print(QUEUE hQueue){
    Queue* pQueue = (Queue*) hQueue;
    if (pQueue->head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    pNode temp = pQueue->head;
    while (temp) {
        printf("%d",temp->data);
        printf(" ");
        temp = temp->next;
    }
    printf("\n");
    return;
}
