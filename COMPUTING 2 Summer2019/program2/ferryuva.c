#include <stdio.h>
#include <stdlib.h>

enum status{FAILURE,SUCCESS};
typedef enum status Status;

enum boolean{TRUE, FALSE};
typedef enum boolean Boolean;

enum position{LEFT, RIGHT};
typedef enum position Position;

typedef void* QUEUE;


struct node;
typedef struct node Node;
struct node{
	int data;
	Node* next;
};

struct queue{
	Node *head;
	Node *tail;
};

typedef struct queue Queue;
typedef Queue* Queueptr;


QUEUE queue_init_default(void);

Status queue_enqueue(QUEUE hQueue, int item);

Status queue_dequeue(QUEUE hQueue);

Boolean queue_empty(QUEUE hQueue);

int queue_front(QUEUE hQueue, Status* pStatus);

void queue_destroy(QUEUE *phQueue);

void queue_print(QUEUE hQueue);


int main(int argc, char * argv[]){
	int num;
	scanf("%d",&num);

	for (int i = 0; i < num ; i++){
		int ferry_length;
		int num_of_cars;
		
		scanf("%d %d", &ferry_length, &num_of_cars);
		ferry_length = ferry_length * 100;
		QUEUE hRight = NULL;
		QUEUE hLeft	= NULL;
		hRight = queue_init_default();
		hLeft = queue_init_default();
		int car_length;
		char place[7];
		for (int j = 0; j < num_of_cars; j++){
			scanf("%d",&car_length);
			fgetc(stdin);
			scanf("%s",place);
			if (place[0] == 'l' || place[0] == 'L'){
				queue_enqueue(hLeft,car_length);
			}
			else if (place[0] == 'r' || place[0] == 'R'){
				queue_enqueue(hRight,car_length);
			}
		}
		int trip_count = 0;
		int ferry;
		Position ferry_position = LEFT;
		Status left_status = SUCCESS;
		Status right_status = SUCCESS;
		while(!queue_empty(hLeft) || !queue_empty(hRight)){
			ferry = 0;
			if (ferry_position == LEFT){
				while(!queue_empty(hLeft) && (ferry + queue_front(hLeft,&left_status)) <= ferry_length)
				{
					ferry = ferry + queue_front(hLeft,&left_status);
					queue_dequeue(hLeft);
				}
				ferry_position = RIGHT;
			}
			else if (ferry_position == RIGHT){
				while(!queue_empty(hRight) && (ferry + queue_front(hRight,&right_status)) <= ferry_length)
				{
					ferry = ferry + queue_front(hRight,&right_status);
					queue_dequeue(hRight);
				}
				ferry_position = LEFT;
			}
			trip_count++;
		}
		printf("%d\n",trip_count);
		queue_destroy(&hLeft);
		queue_destroy(&hRight);
		
	}
}



QUEUE queue_init_default(void){
	Queueptr pQueue = (Queueptr)malloc(sizeof(Queue));
	if (pQueue != NULL){
		pQueue->head = NULL;
		pQueue->tail = NULL;
	}
	return pQueue;
}

Status queue_enqueue(QUEUE hQueue, int item)
{
	Queueptr pQueue = (Queueptr)hQueue;
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL){
		return FAILURE;
	}
	temp->data = item;
	temp->next = NULL;
	if (pQueue->head == NULL){
		pQueue->head = temp;
		pQueue->tail = temp;
	}
	else {
		pQueue->tail->next = temp;
		pQueue->tail = temp;
	}
	return SUCCESS;
}

Status queue_dequeue(QUEUE hQueue){
	Queueptr pQueue = (Queueptr)hQueue;	
	if (queue_empty(hQueue)){
		return FAILURE;
	}
	Node *temp;
	temp = pQueue->head;
	pQueue->head = pQueue->head->next;
	if (pQueue->head == NULL){
		pQueue->tail = NULL;
	}
	free(temp);
	return SUCCESS;
}

Boolean queue_empty(QUEUE hQueue){
	Queueptr pQueue = (Queueptr)hQueue;
	return (Boolean)(pQueue->head == NULL);
}

int queue_front(QUEUE hQueue, Status* pStatus){
	Queueptr pQueue = (Queueptr)hQueue;
	if (pQueue == NULL){
		*pStatus = FAILURE;
		return -1;
	}
	if (pQueue->head == NULL){
		*pStatus = FAILURE;
		return -1;
	}
	int hold = pQueue->head->data;
	*pStatus = SUCCESS;
	return hold;
}

void queue_destroy(QUEUE *phQueue){
	Queueptr pQueue = (Queueptr) *phQueue;
	while(pQueue->head != NULL){
		Node *temp = pQueue->head;
		pQueue->head = pQueue->head->next;
		free(temp);
	}
	free(*phQueue);
	*phQueue = NULL;
	return;
}

void queue_print(QUEUE hQueue){
    Queueptr pQueue = (Queueptr) hQueue;
    if (pQueue->head == NULL) {
        printf("Queue is empty\n");
        return;
    }
    Node *temp = pQueue->head;
    while (temp != NULL){
        printf("%d",temp->data);
        printf(" ");
        temp = temp->next;
    }
    printf("\n");
    return;
}ta);
        printf(" ");
        temp = temp->next;
    }
    printf("\n");
    return;
}