#ifndef _HOME_DAPHNE_PS5A_RINGBUFFER_H_
#define _HOME_DAPHNE_PS5A_RINGBUFFER_H_
// Copyright 2015 fredm@cs.uml.edu for 91.204 Computing IV
#include <stdint.h>


class RingBuffer {
 public:
explicit RingBuffer(int capacity);
int size();
bool isEmpty();
bool isFull();
void enqueue(int16_t x);
int16_t dequeue();
int16_t peek();
int16_t *ringBuffer;
 private:
int Capacity;
int _size;
int head;
int tail;
};

#endif  // _HOME_DAPHNE_PS5A_RINGBUFFER_H_
