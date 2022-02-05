#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "linked_list.h"

int main(int argc, char* argv[])
{

	pLinkedList list = linkedlistInitDefault();

	linkedlistScanInit(list);
	printf("Before sorting:\n");


	printf("Current list\n");
	linkedlist_display(list);


	printf("\nAfter sorting:\n");
	selection_sort(list);
	linkedlist_display(list);
	printf("\n");


	linkedlistDestroy(&list);

	return 0;
}