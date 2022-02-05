#include <stdio.h>
#include <stdlib.h>
#include "vector.h"

int main(int argc, char* agrv[]) {
	//Step 1: Declare the handle

	VECTOR hVector = NULL;
	int i;
	//Step 2: init the object
	hVector = vector_init_default();
	printf("The size of the vector is %d\n", vector_get_size(hVector));
	printf("The capacity of the vector is %d\n", vector_get_capacity(hVector));

	//Step 3: use object
	//add item
	//vector_push_back(hVector, 100);
	/*for (i = 0; i < 5; i++) {
	if (vector_push_back(hVector, i) == FAILURE) {
	printf("Failed to add item\n");
	exit(1);
	}
	printf("The size of the vector is %d\n", vector_get_size(hVector));
	printf("The capacity of the vector is %d\n", vector_get_capacity(hVector));
	printf("%d\n", vector_at(hVector, i));
	}*/


	for (i = 0; i < 5; i++) {
		if (vector_push_back(hVector, i) == FAILURE) {
			printf("Failed to add item\n");
			exit(1);
		}
		printf("The size of the vector is %d\n", vector_get_size(hVector));
		printf("The capacity of the vector is %d\n", vector_get_capacity(hVector));
	}
	printf("The size of the vector is %d\n", vector_get_size(hVector));
	printf("The capacity of the vector is %d\n", vector_get_capacity(hVector));
	for (i = 0; i < vector_get_size(hVector); i++) {

		printf("%d\n", vector_at(hVector, i));
	}
	/*for (i = 0; i < 2; i++) {
	if (vector_pop_back(hVector) == FAILURE) {
	printf("Failed to remove item\n");
	exit(1);
	}
	printf("The size of the vector is %d\n", vector_get_size(hVector));
	printf("The capacity of the vector is %d\n", vector_get_capacity(hVector));
	}*/

	//Step 4: Destroy object
	vector_destroy(&hVector);

	return 0;
}