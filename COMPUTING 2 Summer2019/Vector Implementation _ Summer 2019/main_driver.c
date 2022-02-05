#include "int_vector.h"

// main driver
int main(void){
	//declaration
	MY_VECTOR hVector; // 4 bytes used
	hVector = int_vector_init_default();
	
	if (hVector == NULL){
		 printf(" No memory \n");
	}
	DATATYPE item;
	
	//pushed items into the array
	for (int i=0; i<20; i++){
		item = rand()%100;
		int_vector_push(hVector, item);
		
	}
	
	//check the size
	printf("Size: %d \n", int_vector_getSize(hVector));
	printf("Size: %d \n", int_vector_getCapacity(hVector));

	
	int_vector_printContents (hVector);
	
	int_vector_destroy (&hVector);
	
	return 0;
}

