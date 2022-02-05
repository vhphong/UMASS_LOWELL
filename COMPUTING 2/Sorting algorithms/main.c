#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int number[], int size);
void swap(int* a, int* b);
void selection_sort(int number[], int size);
int find_index(int number[], int size, int start_index);
void insertion_sort(int number[], int size);
void insertion_sort_with_shift(int number[], int size);
void insertion_sort_with_shift_sentinel(int number[], int size);
void shell_sort(int number[], int size);
void quick_sort(int number[], int size);

int main()
{
	int i;
	int number[] = { 1,5,3,0,4,2, 8,7,9,6 };
	for (i = 0; i < 10; i++)
		printf("%d\n", number[i]);
	printf("----------\n");
//	bubble_sort(number, 10);
//	selection_sort(number, 10);
	shell_sort(number, 10);
	for (i = 0; i < 10; i++)
		printf("%d\n", number[i]);
	getchar();
	return 0;
}
void swap(int* a, int* b)
{
	int temp;
	temp = *a;
	*a = *b;
	*b = temp;
}
void bubble_sort(int number[], int size) {
	int i, j;
	int is_swapped = 1;
	for (i = 0; i < size - 1 && is_swapped; ++i) {
		for (j = 0; j < size - 1 - i; ++j) {
			is_swapped = 0;
			if (number[j] > number[j + 1]) {
				swap(&number[j], &number[j + 1]);
				is_swapped = 1;
			}
		}
	}
}

void selection_sort(int number[], int size) {
	int i;
	int index_smallest;
	for (i = 0; i < size; ++i) {
		index_smallest = find_index(number, size, i);
		swap(&number[i], &number[index_smallest]);
	}
}

int find_index(int number[], int size, int start_index) {
	int i;
	int index_of_min = start_index;
	for (i = start_index; i < size; i++) {
		if (number[i] < number[index_of_min])
			index_of_min = i;
	}
	return index_of_min;
}
void insertion_sort(int number[], int size) {
	int i, j;
	for (i = 1; i < size; i++) {
		j = i;
		while (j - 1 >= 0 && number[j] < number[j - 1]) {
			swap(&number[j - 1], &number[j]);
			j--;
		}
	}
}
void insertion_sort_with_shift(int number[], int size) {
	int i, j, temp;
	for (i = 1; i < size; i++) {
		j = i;
		temp = number[j];
		while (j - 1 >= 0 && temp < number[j - 1]) {
			number[j] = number[j - 1];
			j--;
		}
		number[j] = temp;
	}
}
void insertion_sort_with_shift_sentinel(int number[], int size) {
	int i, j, temp;
	swap(&number[0], number[find_index(number, size, 0)]);
	for (i = 1; i < size; i++) {
		j = i;
		temp = number[j];
		while (temp < number[j - 1]) {
			number[j] = number[j - 1];
			j--;
		}
		number[j] = temp;
	}
}

void shell_sort(int number[], int size) {
	int i,j, h;
	h = size / 3 + 1;
	do {
		h--;
		for (i = h; i < size; ++i) {
			j = i;
			while (j - h >= 0 && number[j] < number[j - h]) {
				swap(&number[j - h], &number[j]);
			}
		}
	} while (h != 1);

}
void quick_sort(int number[], int size) {
	//pick up pivot
	// two pointers: left & right
	// everything on the left from pivot is smaler than pivot
	//everything on the right is larger
	int left;
	int right;
	int pivot;
	pivot = 0;
	left = 0;
	right = size - 1;
	if (size < 2) {
		return;
	}
	while (left < right) {
		while (right > left && number[right] > number[pivot]) {
			right--;
		}
		while (left < right && number[left] <= number[pivot]) {
			left++;
		}
		if (left != right) {
			swap(&number[left], &number[right]);
		}
		else {
			swap(&number[pivot], &number[left]);
		}
	}
	quick_sort(number, left);
//	quick_sort(number[left + 1], size - 1 - left);
	quick_sort(number + left + 1, size - 1 - left);

}