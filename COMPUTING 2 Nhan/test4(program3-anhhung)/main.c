/**********************************************************************
Program: Number Filter
Author: Hoang Do
Date: 10/31/2017
Time spent: 5 hours
Purpose: Using linklist and Algorithms to sort a list of number with duplicate
***********************************************************************/

#define _CRT_SECURE_NO_WARNINGS //for visual studio: scanf error
#include<stdio.h>
#include<stdlib.h>

struct node  {
	int data;
	struct node* next;
	};

struct node* head;

typedef struct node Node;

void InsertSort(Node** pHead, int item);
void Print(Node* head);
void destroy(Node** pHead);
	
int main() {
	int number = 0;
	Node* head = NULL;
	scanf("%d", &number);
	while (number >= 0){
		InsertSort(&head, number);
		scanf("%d", &number);
	}
	Print(head);
	destroy(&head);
	return 0;
}

//Inserts a Node in the right order
void InsertSort(Node** pHead, int item) {
	Node* temp;
	Node* current;
	Node* prev = NULL;
	current = *pHead;
	temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL) {
		printf("no memory allocated\n");
		exit(1);
	}
	temp->data = item;
	temp->next = NULL;
	
	if(current == NULL){
		temp->next = NULL;
		(*pHead) = temp;
		return;
	}
	if (item < current->data){
		temp->next = *pHead;
		*pHead = temp;
		return;
	}
	else if (item == current->data){
		free(temp);
		return;
	}
	else{
		while(current != NULL){
			if(item == current->data){
				free(temp);
				return;
			}else if (item > current->data){
				prev = current;
			}else{
				prev->next = temp;
				temp->next = current;
				return;
			}
			current = current->next;
		}
		prev->next = temp;
	}
}

void Print(Node* head) {
	Node* temp = head;
	printf("Sorted list: ");
	while(temp != NULL) {
		printf("%d ",temp->data);
		temp = temp->next;
	}
	printf("\n");
}

void destroy(Node** pHead) {
	Node* temp;
	temp = *pHead;
	while (temp != NULL) {
		*pHead = temp->next;
		free(temp);
		temp = *pHead;
	}
}
