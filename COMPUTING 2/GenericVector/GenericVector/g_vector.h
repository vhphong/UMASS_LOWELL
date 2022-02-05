#ifndef VECTOR_H
#define VECTOR_H
#include "status.h"

typedef void* G_VECTOR;

G_VECTOR g_vector_init_default(Status(*item_assign)(Item_ptr, Item),
	void(*item_destroy)(Item_ptr));
//add item
Status g_vector_push_back(G_VECTOR hVector, Item item);
//delete item
Status g_vector_pop_back(G_VECTOR hVector);
//see a particular value
Item g_vector_at(G_VECTOR hVector, int index);
// return size and capacity
int g_vector_get_size(G_VECTOR hVector);
int g_vector_get_capacity(G_VECTOR hVector);

//destroy the object
void g_vector_destroy(G_VECTOR* phVector);

#endif