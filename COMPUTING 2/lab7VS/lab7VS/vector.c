#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"

//example of destroy function
//void (*p_destroy)(Item* phInt); //how to declare pointer to function
void integer_destroy(Item* phInt)  //was (int** phInt) pointer to the handle
{
	int* pInt = (int*)*phInt; //dereference to the known type
	free(pInt);
	printf("Destroying an integer\n");
	*phInt = NULL;
}
 Status integer_assign(Item* phLeft, Item right)
{
	int* pLeft = (int*)*phLeft;
	int* pRight = (int*)right;
	printf("Assigning an integer\n");
	if (pLeft == NULL)//left handside does not exist
	{
		printf("creating space\n");
		pLeft = (int*)malloc(sizeof(int));
		if (pLeft == NULL)
		{
			printf("FAILED\n");
			return FAILURE;
		}
		*phLeft = pLeft;//dereference pLeft It came as NULL need to reassign it
	}
	*pLeft = *pRight;//not NULL copy integer
	return SUCCESS;
}

int main(int argc, char* argv[])
{
	G_VECTOR hVector = NULL;
	int x = 42;
	int i;
	hVector = generic_vector_init_default(integer_assign,integer_destroy);
	if (hVector == NULL)
	{
		printf("Did not creat vector\n");
		exit(1);
	}
	generic_vector_push_back(hVector, &x);
	x = 100;
	generic_vector_push_back(hVector, &x);
	x = 37;
	generic_vector_push_back(hVector, &x);
	generic_vector_pop_back(hVector);
	generic_vector_push_back(hVector, &x);

	for (i = 0; i < generic_vector_get_size(hVector); i++) {
		printf("%d: %d\n", i,*(int*)generic_vector_at(hVector, i));//(*int)integer pointer * dereference
	}
	generic_vector_destroy(&hVector);
 //integer_destroy(NULL);

	return 0;
}
