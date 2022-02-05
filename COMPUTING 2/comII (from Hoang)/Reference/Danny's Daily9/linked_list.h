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

pLinkedList linkedlistInitDefault();

int linkedlistGetSize(pLinkedList list);

void linkedlistAddNodeBack(pLinkedList list, Item item);

void linkedlistDestroy(pLinkedList *list);

void linkedlist_display(pLinkedList list);

void selection_sort(pLinkedList list);

Node_Ptr linkedlist_find_min(Node_Ptr pNode);

void swap(Node_Ptr left, Node_Ptr right);

int less(Item left, Item right);
