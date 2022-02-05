#include<stdio.h>
#define maxsize 10

int stack[maxsize];
int top = -1;

//function prototypes
void push(int item);
void pop();
void print();
int isEmpty(); // will return 1 if False , 0 if true;

int main(int argc, char** argv) {

	int n = 5;

	for (int i = 0; i < 5; ++i) {
		push(rand()%100);
	}

	print();

	pop();
	print();
	pop();
	print();
	pop();
	print();

	push(678);
	print();

	printf("\nif Empty value will be 1: %d \n", isEmpty());

	return 0;
}
//function definitions
void push(int item) {
	++top;
	stack[top] = item;

}
void pop() {
	if (top >= 0)
		top--;
}

void print() {
	for (int i = top; i >= 0; i--) {
		printf("%d: %d \n", i, stack[i]);
	}
	printf("***END**** \n");

}

int isEmpty() {
	if (top >= 0)
		return 0;

	return 1;
}