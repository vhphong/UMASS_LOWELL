//  Copyright 2018 Dangnhi Ngo
#ifndef _HOME_DAPHNE_PS5B_RINGBUFFER_H_
#define _HOME_DAPHNE_PS5B_RINGBUFFER_H_
#include <stdint.h>
#include <iostream>
#include <stdexcept>
#include <vector>

class RingBuffer {
 public:
explicit RingBuffer(int Capacity);
int Size();
bool isEmpty();
bool isFull();
void enqueue(int16_t x);
int16_t dequeue();
int16_t peek();
 private:
std::vector<int16_t> ringBuffer;
int capacity;
int size;
int head;
int tail;
};


#endif  // _HOME_DAPHNE_PS5B_RINGBUFFER_H_
