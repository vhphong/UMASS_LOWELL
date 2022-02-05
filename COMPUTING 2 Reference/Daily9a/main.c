#include <stdio.h>
#include <stdlib.h>
#include "item.h"
#include "linked_list.h"

int main(int argc, char* argv[])
{

	pLinkedList list = linkedlistInitDefault();

	linked_list_Scan(list); //scan strings
	printf("Before sorting: ");
	printf("Current list\n");
	linkedlist_display(list); //display current strings

	printf("\nAfter sorting: "); 
	selection_sort(list); //sort
	linkedlist_display(list); //display after sorting
	printf("\n");


	linkedlistDestroy(&list);
	
	return 0;
}