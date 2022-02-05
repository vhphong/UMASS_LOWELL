#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{

	int i = 0;
	int j;
	
	int size;

	int **pArray = (int**)malloc(20 * sizeof(int*));
	
	
	for (i = 0; i < 20; i++) {
		pArray[i] = (int*)malloc(30 * sizeof(int));
	}

	
	
	
	for (i = 0; i < 20; i++) {
		for (j = 0; j < 30; j++) {
			pArray[i][j] = i + j;
		}

	}



	for (i = 0; i<20; i++) {
		printf("\n");
		for (j = 0; j<30; j++) {
			printf("%5d", pArray[i][j]);
		}
	}

	


	for (i = 0; i<20; i++)
		free(pArray[i]);

	free(pArray);//free harambe

	

	
	

	
	

	return 0;
}
