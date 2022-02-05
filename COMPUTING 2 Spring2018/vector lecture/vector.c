#include <stdio.h>
#include <stdlib.h>
#include "vector.h"
#include "status.h"

struct vector {
	int size;
	int capacity;
	int* data;
};
typedef struct vector Vector;


VECTOR vector_init_default(void) {
	Vector* pVector;
	pVector = (Vector*)malloc(sizeof(Vector));
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (int*)malloc(sizeof(int)*pVector->capacity);
		if (pVector->data == NULL) {
			//object was not created
			free(pVector);
			pVector = NULL;
		}
	}
	return pVector;
}
//add item
Status vector_push_back(VECTOR hVector, int item) {
	Vector* pVector = (Vector*)hVector;
	int* temp;
	int i;

	if (pVector->size >= pVector->capacity) {
		temp = (int*)malloc(sizeof(int) * 2 * pVector->capacity);
		if (temp == NULL) {
			return FAILURE;
		}
		for (i = 0; i < pVector->capacity; i++) {
			temp[i] = pVector->data[i];
		}
		free(pVector->data);
		pVector->data = temp;
		pVector->capacity *= 2;
	}
	pVector->data[pVector->size] = item;
	pVector->size++;
	return SUCCESS;
}

//delete item
Status vector_pop_back(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	if (pVector->size <= 0) {
		return FAILURE;
	}
	pVector->size--;
	return SUCCESS;
}
//see a particular value
int vector_at(VECTOR hVector, int index) {
	Vector* pVector = (Vector*)hVector;
	if (index < 0 || index >= pVector->size) {
		return NULL;
	}
	return pVector->data[index];    //pVector->data+index;
}
// return size and capacity
int vector_get_size(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	return pVector->size;
}
int vector_get_capacity(VECTOR hVector) {
	Vector* pVector = (Vector*)hVector;
	return pVector->capacity;
}

void vector_destroy(VECTOR* phVector) {
	Vector* pVector = (Vector*)*phVector;
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}