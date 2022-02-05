#include <stdio.h>
#include <stdlib.h>
#include "g_vector.h"

Status integer_assign(Item_ptr phLeft, Item pRight);


void integer_destroy(Item_ptr phInt);

int main(int argc, char* agrv[]) {
	//Step 1: Declare the handle

	G_VECTOR hG_VECTOR = NULL;
	int i, n;
	//Step 2: init the object
	hG_VECTOR = g_vector_init_default(integer_assign, integer_destroy);
	printf("The size of the G_VECTOR is %d\n", g_vector_get_size(hG_VECTOR));
	printf("The capacity of the G_VECTOR is %d\n", g_vector_get_capacity(hG_VECTOR));

	//Step 3: use object
	//add item
	//g_vector_push_back(hG_VECTOR, 100);
	for (i = 0; i < 5; i++) {
		if (g_vector_push_back(hG_VECTOR, &i) == FAILURE) {
			printf("Failed to add item\n");
			exit(1);
		}
		printf("The size of the G_VECTOR is %d\n", g_vector_get_size(hG_VECTOR));
		printf("The capacity of the G_VECTOR is %d\n", g_vector_get_capacity(hG_VECTOR));
		printf("%d  %d\n", *(int*)g_vector_at(hG_VECTOR, i), g_vector_at(hG_VECTOR, i));
	}

	//Step 4: Destroy object
	g_vector_destroy(&hG_VECTOR);
	return 0;
}
Status integer_assign(Item_ptr phLeft, Item Right) {
	int* pLeft = (int*)*phLeft;
	int* pRight = (int*)Right;
	if (pLeft == NULL) {
		pLeft = (int*)malloc(sizeof(int));
		if (pLeft == NULL)
			return FAILURE;
		*phLeft = pLeft;
	}
	*pLeft = *pRight;
	return SUCCESS;
}

void integer_destroy(Item_ptr phInt) {
	int* pInt = (int*)*phInt;
	free(pInt);
	*phInt = NULL;
}
