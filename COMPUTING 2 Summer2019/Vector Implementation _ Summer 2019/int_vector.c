

#include "int_vector.h"
//KNOWN TYPE
struct vector{
	int size; // number of items in the array
	int capacity; // total capacity of array
	DATATYPE* data;
	
};

typedef struct vector Vector;

// function definitions
MY_VECTOR int_vector_init_default(){
	
	Vector* pVector=(Vector*) malloc (sizeof(Vector));
	
	
	if (pVector == NULL){
		printf("No Memory \n");
		exit(1);
	}
	
	//initialization
	pVector->capacity= 7;
	pVector->size = 0;
	pVector->data = (DATATYPE*) malloc (sizeof(DATATYPE) * pVector->capacity);
	if ((pVector->data) == NULL){
		free(pVector);
		pVector = NULL;
	}

	return (MY_VECTOR) pVector;
	
}

Status int_vector_push(MY_VECTOR hVector, DATATYPE item){
	Vector* pVector = (Vector*) hVector;
	
	int* tempData;
	if (int_vector_is_full(pVector)){
		tempData = (int*) malloc (sizeof(int) * (pVector->capacity *2));
		if (tempData == NULL){
			return Failure;
		}
		for (int i =0;i<pVector->size; i++){
				tempData[i] = pVector->data[i];
		}
		free(pVector->data);
		pVector->data = tempData;
		pVector->capacity= pVector->capacity*2;
	}
	pVector->data[pVector->size] = item;
	pVector->size++;
	
	return Success;
	
}
////check whether array is full
Boolean int_vector_is_full(MY_VECTOR hVector){
	Vector* pVector = (Vector*) hVector;
	if (pVector->size>= pVector->capacity){
		return True;
	}
	return False;
	
}
//check whether array is empty
Boolean int_vector_is_empty(MY_VECTOR hVector){
	Vector* pVector = (Vector*) hVector;
	if (pVector->size <=0){
		return True;
	}
	return False;
	
}

// Accessor function to get the total items in the array
int int_vector_getSize(MY_VECTOR hVector){
	Vector* pVector = (Vector*) hVector;
	return pVector->size;
}

int int_vector_getCapacity(MY_VECTOR hVector){
	Vector* pVector = (Vector*) hVector;
	return pVector->capacity;
}

// remove items from the array
Status int_vector_pop (MY_VECTOR hVector){
	Vector* pVector = (Vector*) hVector;
	if (!int_vector_is_empty(pVector)){
		pVector->size--;
		return Success;
	}
	return Failure;
	
}

void int_vector_printContents(MY_VECTOR hVector){
	Vector* pVector = (Vector*) hVector;
	//print all array items
	for (int i=0; i<pVector->size; i++){
		printf("%d \n", pVector->data[i] );
	}
	
}
//free up all the memory
void int_vector_destroy(MY_VECTOR* phVector){
	Vector* pVector = (Vector*) *phVector;
	if (pVector != NULL){
		free(pVector->data);
		free(pVector);
	}
	*phVector = NULL;
}


