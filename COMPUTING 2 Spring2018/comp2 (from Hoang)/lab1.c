#include <stdio.h>
#include <stdlib.h>
#define ROWS 20
#define COLS 30

int main(void)
{
	int **arr;
	int start = 0;
 	arr  = (int**)malloc(ROWS * sizeof(int*));
 	for (int i = 0; i < ROWS; i++)
 		arr[i] = (int*)malloc(COLS * sizeof(int));
    
    for (int i = 0; i < ROWS; i++){
    	for (int j = 0; j < COLS; j++){
    		arr[i][j]= j + start; 
		}
		start++;
	}
	
    printf("Hello world! I have created a dynamic 2D-array of 20x30 integers!\n");
    
	for (int i = 0; i < ROWS; i++){
    	for (int j = 0; j < COLS; j++){
    		printf("%3d",arr[i][j]); 
		}
		printf("\n");
	}	
   return 0;
}
