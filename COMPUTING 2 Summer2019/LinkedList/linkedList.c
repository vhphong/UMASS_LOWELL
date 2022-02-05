#include <stdio.h>
#include <stdlib.h>

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
};

//Node* head_insert(Node* head, int item);
void head_insert(Node** pHead, int item);
void tail_insert(Node** pHead, int item);

void print_list(Node* head);

void destroy_list(Node** pHead);

int main(int argc, char* argv[])
{
	Node* head = NULL;

	head_insert(&head, 68);

	tail_insert(&head, 42);
	tail_insert(&head, 107);
	tail_insert(&head, 9001);
	tail_insert(&head, 54);

	print_list(head);

	destroy_list(&head);

	return 0;
}

void head_insert(Node** pHead, int item)
{
	Node* temp;

	temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		printf("Failed to allocate memory for a new node.\n");
		exit(1);
	}
	temp->data = item;
	temp->next = *pHead;
	*pHead = temp;
}

//Node* head_insert(Node* head, int item)
//{
//	Node* temp;
//
//	temp = (Node*) malloc(sizeof(Node));
//	if (temp == NULL)
//	{
//		printf("Failed to allocate memory for a new node.\n");
//		exit(1);
//	}
//	temp->data = item;
//	temp->next = head;
//	head = temp;
//	return head;
//}

void print_list(Node* head)
{
	while (head != NULL)
	{
		printf("%d\n", head->data);
		head = head->next;
	}
}

void destroy_list(Node** pHead)
{
	Node* temp;
	while (*pHead != NULL)
	{
		temp = *pHead;
		*pHead = (*pHead)->next;
		free(temp);
	}
}

void tail_insert(Node** pHead, int item)
{
	Node* temp;

	if (*pHead == NULL)
	{
		*pHead = (Node*)malloc(sizeof(Node));
		(*pHead)->data = item;
		(*pHead)->next = NULL;
	}
	else
	{
		temp = *pHead;
		while (temp->next != NULL)
		{
			temp = temp->next;
		}
		temp->next = (Node*)malloc(sizeof(Node));
		temp->next->data = item;
		temp->next->next = NULL;
	}
}

//void tail_insert(Node** pHead, int item)
//{
//	if ((*pHead) == NULL)
//	{
//		*pHead = (Node*)malloc(sizeof(Node));
//		if (*pHead == NULL)
//		{
//			printf("failed to allocate space for node.\n");
//			exit(1);
//		}
//		(*pHead)->data = item;
//		(*pHead)->next = NULL;
//	}
//	else
//	{
//		tail_insert(&((*pHead)->next), item);
//	}
//	
//}