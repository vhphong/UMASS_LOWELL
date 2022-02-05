#include <stdio.h>
#include <stdlib.h>

typedef void* VECTOR;

enum status { FAILURE, SUCCESS };
typedef enum status Status;

void swap(int* a, int* b);
int partition (int arr[], int low, int high);
void quickSort(int arr[], int low, int high);
void printArray(int arr[], int size);
int removeDuplicates(int arr[], int n);

VECTOR vector_init_default(void);
int vector_get_size(VECTOR hVector);
void vector_destroy(VECTOR* phVector);
Status vector_push_back(VECTOR hVector, int item);
void sort_arr(VECTOR hVector);

struct vector 
{
	int size;
	int capacity;
	int* data;
};

typedef struct vector Vector;

int main(int argc, char* agrv[])
{
    VECTOR hVector = NULL;
    hVector = vector_init_default();
    int i;
    do
    {
        scanf("%d",&i);
        if (i > -1 && vector_push_back(hVector, i) == FAILURE)
		{
			printf("Cannot add item\n");
			exit(1);
		}
    }while(i != -1);
    sort_arr(hVector);
    vector_destroy(&hVector);
    return 0;
}



VECTOR vector_init_default(void)
{
	Vector* pVector;
	pVector = (Vector*)malloc(sizeof(Vector));
	if (pVector != NULL)
	{
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (int*)(malloc(sizeof(int)*pVector->capacity));
		if (pVector->data == NULL)
		{
			free(pVector);
			pVector = NULL;
		}
	}
	
	return pVector;
}

int vector_get_size(VECTOR hVector)
{
	Vector* pVector = (Vector*)hVector;
	return pVector->size;

}

Status vector_push_back(VECTOR hVector, int item)
{
	Vector* pVector = (Vector*)hVector;
	int* temp;
	int i;
	if (pVector->size >= pVector->capacity)
	{
		temp = (int*)malloc(sizeof(int) * 2 * pVector->capacity);
		if (temp == NULL)
		{
			return FAILURE;
		}
		for (i = 0; i < pVector->size; i++)
		{
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

void vector_destroy(VECTOR* phVector)
{
	Vector* pVector=(Vector*)*phVector;
	free(pVector->data);
	free(pVector);
	*phVector = NULL;
}

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int partition (int arr[], int low, int high)
{
    int pivot = arr[high];
    int i = (low - 1); 
 
    for (int j = low; j <= high- 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;    
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high)
{
    if (low < high)
    {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void printArray(int arr[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int removeDuplicates(int arr[], int n)
{
    if (n==0 || n==1)
        return n;
 

    int j = 0;

    for (int i=0; i < n-1; i++)
        if (arr[i] != arr[i+1])
            arr[j++] = arr[i];
 
    arr[j++] = arr[n-1];
 
    return j;
}
void sort_arr(VECTOR hVector)
{
    Vector* pVector = (Vector*)hVector;
    int n = vector_get_size(pVector);
    quickSort(pVector->data,0,n-1);
    n = removeDuplicates(pVector->data,n);
    printArray(pVector->data,n);
}