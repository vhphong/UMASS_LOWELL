/***********************************************************
Author: <Rushabh Doshi>
Date: <11/25/2016>
Effort: <30 minutes>
Purpose: <practice algorithms (merge sort)>
***********************************************************/
#include<stdio.h>
#include<stdlib.h>
#include <time.h>

void merge(int a[], int low, int mid, int high);
void mergesort(int a[], int low, int high);

int main(int argc, char* argv[]) {

	int a[200];
	int i;
	int j = 0;
	printf("How many random elements do you want to sort?:");
	scanf("%d", &i);
	
	srand(time(NULL));
	for (j = 0; j < i; j++)
	{
		a[j] = rand() % 100 ;
	}

	printf("Before sort\n");
	//prints the array of random elements inerted
	for (j = 0; j < i; j++)
	{
		printf("%d ", a[j]);
	}
	printf("\n");
	int numberOfElements = i;
	
	printf("-------------------[%d] elements [%d] ----------------------\n", numberOfElements, numberOfElements);


	mergesort(a, j = 0, numberOfElements - 1);
	
	printf("After sort\n");
	//prints array after random elements were sorted
	for (j = 0; j < i; j++)
	{
		printf("%d ", a[j]);
	}
	printf("\n");
	
	return 0;
}

void merge(int a[], int low, int mid, int high)
{
	int b[10000];
	int i, j, k;
	i = low;
	j = mid + 1;
	k = 0;

	while (i <= mid && j <= high) {
		if (a[i] <= a[j])
			b[k++] = a[i++];
		else
			b[k++] = a[j++];
	}
	while (i <= mid)
		b[k++] = a[i++];

	while (j <= high)
		b[k++] = a[j++];

	k--;
	while (k >= 0) {
		a[low + k] = b[k];
		k--;
	}
}
 
void mergesort(int a[], int low, int high)
{
	int m;
	
	if (low < high) {
		m = (high + low) / 2;
		mergesort(a, low, m); 
		mergesort(a, m + 1, high);
		merge(a, low, m, high);
	}
}
