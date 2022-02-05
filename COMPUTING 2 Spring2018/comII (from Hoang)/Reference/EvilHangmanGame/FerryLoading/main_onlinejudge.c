
/**********************************************************************
 Program: Daily 7
 Author: Viet Tran Quoc Hoang
 Date: 2/27/2016
 Time spent: 2 days
 Purpose: Implementation of stack using linked lists based on parentheses problem
 ***********************************************************************/

enum status { FAILURE, SUCCESS};
typedef enum status Status;
enum boolean { FALSE, TRUE };
typedef enum boolean Boolean;
enum position { LEFT, RIGHT };
typedef enum position Position;

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

QUEUE queue_init_default(void);
Status queue_enqueue(QUEUE hQueue, int item);
Status queue_service(QUEUE hQueue); 
Boolean queue_empty(QUEUE hQueue);
int queue_front(QUEUE hQueue, Status* pStatus);
void queue_destroy(QUEUE* phQueue);
void queue_print(QUEUE hQueue);

// #include "linked_queue.h"
// #include "status.h"
//#define PRINTF//debug comments
//#define uva_will_accept_this
#define alternate_string_method 
#include <string.h>//<--need this to use string functions
#include <stdlib.h>
#include <stdio.h>
int main(int argc, const char * argv[]) {
    int counter;
    scanf("%d",&counter);
    int i;
    for (i = 0; i < counter; i++) {
        int ferry_length;
        int number_of_cars;
        scanf("%d %d",&ferry_length,&number_of_cars);
        ferry_length *= 100;
#ifdef PRINTF
        printf("Ferry length = %d number of cars = %d\n",ferry_length,number_of_cars);
#endif
        int j = 0;
        QUEUE hRightQueue = NULL;
        QUEUE hLeftQueue = NULL;
        hRightQueue = queue_init_default();
        hLeftQueue = queue_init_default();
        
#ifdef alternate_string_method
        int STRING_SIZE = 12; // 9|9|9|9| |R|I|G|H|T|\|0 and +1 to account for empty spaces
        int car_length;
        char line[STRING_SIZE];
        fgetc(stdin);
        while ( j < number_of_cars && fgets(line, STRING_SIZE, stdin) != NULL) {
#ifdef PRINTF
            printf("%s",line);
#endif
            char* string_car_length = strtok(line, " ");//cut at empty space
            char* string_car_position = strtok(NULL,"\n");
            car_length = (int)strtol(string_car_length, NULL, 10);
            if (!strcmp(string_car_position, "left")) {
                hLeftQueue->enqueue(hLeftQueue,car_length);
            }
            else if (!strcmp(string_car_position, "right")){
                hRightQueue->enqueue(hRightQueue,car_length);
           }
            j++;
        }
#endif
        

        
#ifdef uva_will_accept_this
        int car_length;
        int STRING_SIZE = 7; // R|I|G|H|T|\|0 and +1 to account for empty spaces
        char car_position[STRING_SIZE];
        for (j = 0; j < number_of_cars; j++) {
            scanf("%d",&car_length);
            fgetc(stdin);
            scanf("%s",car_position);
            if (car_position[0] == 'l') {
                hLeftQueue->enqueue(hLeftQueue,car_length);
            }
            else{
                hRightQueue->enqueue(hRightQueue,car_length);
            }
        }
#endif
    
#ifdef PRINTF
        
        printf("Left queue:");hLeftQueue->print(hLeftQueue);
        printf("Right queue:");hRightQueue->print(hRightQueue);
        printf("\n");
        
#endif
        
        int trip_counter = 0;
        int ferry_load;
        Status left_queue_status = SUCCESS;
        Status right_queue_status = SUCCESS;
        Position ferry_position = LEFT;
        while (!hRightQueue->empty(hRightQueue) || !hLeftQueue->empty(hLeftQueue)) {
            ferry_load = 0;//reset ferry load after each trip
            if (ferry_position == LEFT){
                while (!hLeftQueue->empty(hLeftQueue) && ferry_load + hLeftQueue->front(hLeftQueue,&left_queue_status)<= ferry_length) {
                    ferry_load += hLeftQueue->front(hLeftQueue,&left_queue_status);
                    hLeftQueue->service(hLeftQueue);
#ifdef PRINTF
                    printf("left loop\n");
                    printf("load = %d\n",ferry_load);
                    printf("Left queue:");hLeftQueue->print(hLeftQueue);
#endif
                    
                }
                ferry_position = RIGHT;//ferry is full,ferry makes the trip
            }
            else if (ferry_position == RIGHT) {
                while (!hRightQueue->empty(hRightQueue) && ferry_load+ hRightQueue->front(hRightQueue,&right_queue_status)<=ferry_length) {
                    ferry_load += hRightQueue->front(hRightQueue,&right_queue_status);
                    hRightQueue->service(hRightQueue);
#ifdef PRINTF
                    printf("right loop\n");
                    printf("load = %d\n",ferry_load);
                    printf("Right queue:");hRightQueue->print(hRightQueue);
#endif
                }
                ferry_position = LEFT;//ferry is full,ferry makes the trip
            }
#ifdef PRINTF
            printf("++\n");
#endif
            trip_counter++;
        }

        
        
#ifdef PRINTF
        printf("\n");
        printf("Left queue:");hLeftQueue->print(hLeftQueue);
        printf("Right queue:");hRightQueue->print(hRightQueue);
        printf("trip counter =");
#endif
        printf("%d\n",trip_counter);
        hLeftQueue->destroy(&hLeftQueue);
        hRightQueue->destroy(&hRightQueue);

    }

    return 0;
}



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

