#include <stdio.h>

void fix_up(int a[], int index);
void swap(int* a, int* b);
void fix_down(int a[], int size, int index);
void heap_sort(int a[], int size);
void heapify(int a[], int size);

int main(int argc, char* argv[])
{
	int numbers[] = { 0,5,2,1,8,3,7,4,6,9 };
	int numbers2[] = { 0,5,2,1,8,3,7,4,6,9 };
	int i;
	/*for (i = 0; i < 10; i++)
	{
		fix_up(numbers, i);
	}*/
	for (i = 0; i < 10; i++)
	{
		printf("%d ", numbers[i]);
	}
	printf("\n");
	heap_sort(numbers, 10);
	/*for (i = 10/2-1; i >=0; i--)
	{
		fix_down(numbers2, 10,i);
	}*/
	for (i = 0; i < 10; i++)
	{
		printf("%d ", numbers[i]);
	}
	printf("\n");
	getchar();
	return 0;
}
void fix_down(int a[], int size, int index)
{
	int left_child_index = 2 * index + 1;
	int right_child_index = 2 * index + 2;
	if (right_child_index < size)
	{
		if (a[left_child_index] > a[right_child_index])
		{
			if (a[left_child_index] > a[index])
			{
				swap(&a[left_child_index], &a[index]);
				fix_down(a, size, left_child_index);
			}
		}
		else 
		{
			if (a[right_child_index] > a[index])
			{
				swap(&a[right_child_index], &a[index]);
				fix_down(a, size, right_child_index);
			}
		}
	}
	else if (left_child_index < size)
	{
		if (a[left_child_index] > a[index])
		{
			swap(&a[left_child_index], &a[index]);
			fix_down(a, size, left_child_index);
		}
	}

}
void fix_up(int a[], int index)
{
	int index_of_parent;
	if (index > 0)
	{
		index_of_parent = (index - 1) / 2;
		if (a[index] > a[index_of_parent])
		{
			swap(&a[index], &a[index_of_parent]);
			fix_up(a, index_of_parent);
		}
	}

}
void swap(int* a, int* b)
{

	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
 }

void heapify(int a[], int size) {
	int i;
	for (i = size / 2 - 1; i >= 0; i--) {
		fix_down(a, size, i);
	}
}

void heap_sort(int a[], int size) {
	heapify(a, size);
	int i, temp;
	int temp_size = size;
	for (i = 0; i < size - 1; i++) {
		temp = a[0];
		a[0] = a[temp_size - 1];
		a[temp_size - 1] = temp;
		temp_size--;
		//fix_down(a, temp_size,0);
		//heap_sort(a, temp_size);
		heapify(a, temp_size);
	}

}