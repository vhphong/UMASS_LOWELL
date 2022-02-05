#include <stdio.h>
#include "queue.h"
int main() {
	QUEUE hQueue;
	Status q_status;
	q_status = SUCCESS;
	int i = 0;
	hQueue = queue_init_default();
	if (hQueue == NULL) {
		printf("Failed to allocate memory\n");
	}
	while (queue_enqueue(hQueue, i) == SUCCESS && i < 6) {
		printf("i = %d", i);
		i++;
	}
	queue_print(hQueue);
	printf("dequeue------\n");
	queue_dequeue(hQueue);
	queue_dequeue(hQueue);
	queue_dequeue(hQueue);
	printf("after dequeue------\n");

	queue_print(hQueue);
	printf("------\n");
	printf("enqueue------\n");

	queue_enqueue(hQueue, 6);
	queue_enqueue(hQueue, 7);
	queue_enqueue(hQueue, 8);
	printf("------\n");
	queue_print(hQueue);

	queue_destroy(&hQueue);
	if (hQueue == NULL)
		printf("Queue destroied!\n");
	return 0;
}