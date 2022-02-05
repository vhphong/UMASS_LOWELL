#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char* argv[])
{
	QUEUE hQueue = NULL;
	int i;

	hQueue = queue_constructor(8);
	if (hQueue == NULL)
	{
		printf("Failed to allocate space for queue object.\n");
		exit(1);
	}

	for (i = 0; i < 10; i++)
	{
		queue_enqueue(hQueue, i);
	}

	while (!queue_empty(hQueue))
	{
		printf("The value at the front is: %d\n", queue_front(hQueue, NULL));
		queue_dequeue(hQueue);
	}
	queue_destroy(&hQueue);


	return 0;
}