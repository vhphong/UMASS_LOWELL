// Copyright 2018 Dangnhi Ngo
#include "RingBuffer.hpp"

RingBuffer::RingBuffer(int Capacity) : capacity(Capacity) {
if (capacity <= 0) {
throw std::invalid_argument("capacity must be greater than zero.");
} else {
ringBuffer.reserve(capacity);
head = capacity-1;
tail = capacity-1;
size = 0;
}
}

int RingBuffer::Size() {
return size;
}

bool RingBuffer::isEmpty() {
if (Size() == 0) {
return true;
} else {
return false;
}
}

bool RingBuffer::isFull() {
if (Size() == capacity) {
return true;
} else {
return false;
}
}

void RingBuffer::enqueue(int16_t x) {
if (!isFull()) {
if (Size() == 0) {
ringBuffer[head] = x;
size++;
} else {
if (tail == 0) {
tail = capacity-1;
ringBuffer[tail] = x;
size++;
} else {
ringBuffer[tail-1] = x;
tail--;
size++;
}
}
} else {
throw std::runtime_error("can't enqueue to a full ring.");
}
}

int16_t RingBuffer::dequeue() {
int16_t temp = ringBuffer[head];
if (!isEmpty()) {
if (head-1 < 0 && Size() > 1) {
ringBuffer[head] = 0;
head = capacity-1;
} else {
ringBuffer[head] = 0;
if (Size() > 1) {
head--;
}
}
size--;
return temp;
} else {
throw std::runtime_error("can't dequeue from an empty ring.");
}
}

int16_t RingBuffer::peek() {
if (!isEmpty()) {
return ringBuffer[head];
} else {
throw std::runtime_error("the ring is empty.");
}
}
