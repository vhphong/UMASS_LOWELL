#ifndef VECTOR_H
#define VECTOR_H
#include "status.h"

typedef void* VECTOR;

VECTOR vector_init_default(void);
//add item
Status vector_push_back(VECTOR hVector, int item);
//delete item
Status vector_pop_back(VECTOR hVector);
//see a particular value
int vector_at(VECTOR hVector, int index);
// return size and capacity
int vector_get_size(VECTOR hVector);
int vector_get_capacity(VECTOR hVector);

//destroy the object
void vector_destroy(VECTOR* phVector);

#endif