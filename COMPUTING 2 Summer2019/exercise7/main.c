/**********************************************************************
Program:  exercise 7
Author:  Phong Vo
Date:    08/01/2019
Time spent:  3 days
Purpose: to learn more about the roles of priority queue
***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(int argc, char*argv[])
{
	PRIORITY_QUEUE hQueue = NULL;
	int i = 0;
	int priority_levels[6] = {22, -3, 99, 0, 156, 4};
	Status status = SUCCESS;

	hQueue = priority_queue_init_default();

	if (hQueue == NULL){
		printf("Failed to allocate data.\n");
		exit(1);
	}

	for (i = 0; i < 6; i++){
		priority_queue_insert(hQueue, priority_levels[i], i);
	}

	while (priority_queue_is_empty(hQueue) != TRUE){
		printf("%d\n", priority_queue_front(hQueue, &status));
		priority_queue_service(hQueue);
	}
	
	priority_queue_destroy(&hQueue);
	return 0;
}