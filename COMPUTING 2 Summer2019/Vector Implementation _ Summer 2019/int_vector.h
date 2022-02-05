#ifndef MY_VECTOR_H
#define MY_VECTOR_H

#include <stdio.h>
#include <stdlib.h>

#include "status.h"

typedef void* MY_VECTOR;

//function prototypes OR function declaration
MY_VECTOR int_vector_init_default();
Status int_vector_push(MY_VECTOR hVector, int item);
Status int_vector_pop (MY_VECTOR hVector);

int int_vector_getSize(MY_VECTOR hVector);
int int_vector_getCapacity(MY_VECTOR hVector);

Boolean int_vector_is_full(MY_VECTOR hVector);
Boolean int_vector_is_empty(MY_VECTOR hVector);


void int_vector_printContents(MY_VECTOR hVector);
void int_vector_destroy(MY_VECTOR* hVector);
#endif