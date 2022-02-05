#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>


//function prototypes
void push(int* stack, int *top, int item);
void pop();
void print();
int isEmpty(); // will return 1 if False , 0 if true;

int main(int argc, char** argv) {
	int *stack;
	int top = -1;

	int n;
	printf("Enter size: ");
	scanf("%d", &n);

	stack = (int*)malloc(sizeof(int)*n);

	for (int i = 0; i < n; ++i) {
		push(stack, &top, rand()%100);
	}

	print(stack, &top);

	pop(&top);
	print(stack, &top);

	printf("\nif Empty value will be 1: %d \n", isEmpty(&top));
	free(stack);

	return 0;
}
//function definitions
void push(int *stack, int *top, int item) {
	++(*top);
	stack[*top] = item;

}
void pop(int *top) {
	if ((*top) >= 0)
		(*top)--;
}

void print(int*stack, int * top) {
	int i=*top;

	while (i!= -1) {
		printf("%d: %d \n", i, stack[i]);
		i--;
	}
	
	printf("***END**** \n");

}

int isEmpty(int *top) {
	if ((*top) >= 0)
		return 0;

	return 1;
}