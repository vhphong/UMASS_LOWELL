/***********************************************************
Author: Phong Vo
Date: 03/18/2018
Effort: 20 hrs
Purpose: Program 2 project
Interface proposal: 
***********************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

//structure to store the details of a car
typedef struct {
	int carLength; //length of car in centimeters
	char carBank[10]; //river bank on which car is at
} Car;

//structure of a node of linked list
typedef struct {
	Car* car;
	struct Node *next;
} Node;

typedef struct {
	Node *head;
	Node *tail;
} Queue;

Queue *left_bank_cars = NULL;
Queue *right_bank_cars = NULL;
/*Node *left_bank_head = NULL; //head node of linked list

Node *left_bank_tail = NULL; //tail node of linked list
Node *right_bank_head = NULL; //head node of linked list
Node *right_bank_tail = NULL; //tail node of linked list*/

//check if Queue is empty
// declaration of the is_empty function
//int is_empty(Queue*);
//void insert_item(Queue*, Car*);
//Car* delete_item(Queue*);

// pointer of the is_empty function
int (*fp_is_empty)(Queue*);
// pointer of the insert_item function
void(*fp_insert_item)(Queue*, Car*);
// pointer of the delete_item function
Car* (*fp_delete_item)(Queue*);
// implementation of the is_empty function

int is_empty(Queue *queue) { 
	return (queue->head == NULL ? 1 : 0);
}

//insert an item at the tail of the list.
//any new item is to be inserted in tail
//of list for it to behave like a queue.
void insert_item(Queue *queue, Car *car) {
	Node* node = (Node*)malloc(sizeof(Node));
	node->car = car;
	node->next = NULL;
	printf("empty:%d\n", fp_is_empty(queue));
	if (!fp_is_empty(queue)) {
		queue->tail->next = node->next;
		queue->tail = node;
		printf("item inserted in tail.\n");
	}
	else {
		queue->tail = node;
		queue->head = node;
		printf("item inserted as head node:%d\n", queue->head->car->carLength);
	}
}

// delete an item from a Queue-list.
// the deleted item was from the head of list
Car* delete_item(Queue *queue) {
	if (fp_is_empty(queue))
		return NULL;
	Car* deleted_item = queue->head->car;
	Node* to_delete = queue->head;
	//queue->head->car = queue->head->next;
	queue->head = queue->tail;
	free(to_delete);
	return deleted_item;
}

//Car* left_bank_cars[MAX_SIZE];
//Car* right_bank_cars[MAX_SIZE];

int main(void) {
	int l; //length of ferry in meters
	int m; //number of cars on any river ferry_bank
	int n; //available capacity on ferry to accommodate cars
	char ferry_bank[5]; //current bank of ferry
	int c; //number of test cases
	int car_length; //length of car in centimeters
	char car_bank[10]; //bank of a car
	int num_left_bank_cars = 0; // number of cars which are on the left bank
	int num_right_bank_cars = 0; // number of cars which are on the right bank
	int num_cars_ferried = 0; // number of cars which are on the ferry
	int num_ferries = 0; // number of sessions of the ferry
	char line[20]; //line containing car details
	char *token;
	
	fp_is_empty = &is_empty;
	fp_insert_item = &insert_item;
	fp_delete_item = &delete_item;

	left_bank_cars = (Queue*)malloc(sizeof(Queue));
	left_bank_cars->head = NULL;
	left_bank_cars->tail = NULL;

	right_bank_cars = (Queue*)malloc(sizeof(Queue));
	right_bank_cars->head = NULL;
	right_bank_cars->tail = NULL;
	
	strcpy(ferry_bank, "left");
	//read number of test cases to execute
	fflush(stdin);
	scanf("%d", &c);
	fflush(stdin);
	//loop to process each test case.
	int i,j; // iterative variables
	for (i = 1; i <= c; i++) {
		//for current test case, read length of ferry and number of cars to be ferried.
		fflush(stdin);
		scanf("%d %d", &l, &m);
		//loop to read car details
		for (j = 1; j <= m; j++) {
			fflush(stdin);
			gets(line);
			token = strtok(line, " ");
			if (token != NULL)
				car_length = atoi(token);
			token = strtok(NULL, " ");
			if (token != NULL)
				strcpy(car_bank, token);
			Car *car = (Car*)malloc(sizeof(Car));
			car->carLength = car_length;
			strncpy(car->carBank, car_bank, strlen(car_bank));
			if (strcmp(car_bank, "left") == 0) {
				//left_bank_cars[num_left_bank_cars] = car;
				fp_insert_item(left_bank_cars, car);
				//printf("left:%d\n",left_bank_cars->head->car->car_length);
				num_left_bank_cars++;
			}
			else if (strcmp(car_bank, "right") == 0) {
				//right_bank_cars[num_right_bank_cars] = car;
				fp_insert_item(right_bank_cars, car);
				num_right_bank_cars++;
			}
			free(car);
		} // end for
		printf("left bank cars: %d\n",num_left_bank_cars);
		printf("right bank cars: %d\n",num_right_bank_cars);
		//now ferry cars for current test case till a car is left on any bank
		while (num_cars_ferried <= m) {
			//printf("in while loop..%d,%d\n",num_cars_ferried,m);
			if (strcmp(ferry_bank, "left") == 0) {
				//printf("On left bank...\n");
				n = l * 100; //available capacity on ferry in centimeters
				while (num_left_bank_cars > 0) {
					if (!fp_is_empty(left_bank_cars)) {
						if (left_bank_cars->head->car->carLength <= n) {
							printf("Decking a car from left...\n");
							Car *car = fp_delete_item(left_bank_cars);
							if (car != NULL) {
								n -= car->carLength;
								num_left_bank_cars--;
								num_cars_ferried++;
								free(car);
							} // end if
						} // end if
					} // end if
					else
						break;
				} // end while
				num_ferries++;
				strcpy(ferry_bank, "right");
				puts(ferry_bank);
			}
			else if (strcmp(ferry_bank, "right") == 0) {
				//printf("On right bank...\n");
				n = l * 100; //available capacity on ferry in centimeters
				while (num_right_bank_cars > 0) {
					if (!fp_is_empty(right_bank_cars)) {
						if (right_bank_cars->head->car->carLength <= n) {
							Car *car = fp_delete_item(right_bank_cars);
							if (car != NULL) {
								n -= car->carLength;
								num_right_bank_cars--;
								num_cars_ferried++;
								free(car);
							}
						}
					}
					else
						break;
				}
				//if(num_cars_ferried==m)
				//break;
				num_ferries++;
				strcpy(ferry_bank, "left");
			}
			printf("Number of cars ferried:%d\n", num_cars_ferried);
			printf("Number of ferries:%d\n", num_ferries);
		}
	}
	return EXIT_SUCCESS;
}
