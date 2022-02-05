#include "item.h"

typedef struct node {
	Item data;
	struct node *next;
} Node, *Node_Ptr;


typedef struct linkedlist {
	Node_Ptr front;
	int size;
	Node_Ptr iterator;

} LinkedList, *pLinkedList;


int linkedlistGetSize(pLinkedList list);
int less(Item left, Item right);
void swap(Node_Ptr left, Node_Ptr right);
void linkedlistAddNodeBack(pLinkedList list, Item item);
void linkedlistDestroy(pLinkedList *list);
void linkedlist_display(pLinkedList list);
void selection_sort(pLinkedList list);
void linked_list_Scan(pLinkedList list);

