#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_
#include <stdint.h>
#include <iostream>
#include <stdexcept>
#include <vector>

class RingBuffer {
	
	public:
		explicit RingBuffer(int Capacity); // create an empty ring buffer, with given max capacity
		int Size(); // return number of items currently in the buffer
		bool isEmpty(); // is the buffer empty (size equals zero)?
		bool isFull(); // is the buffer full  (size equals capacity)?
		void enqueue(int16_t x); // add item x to the end
		int16_t dequeue(); // delete and return item from the front
		int16_t peek(); // return (but do not delete) item from the front
	private:
		std::vector<int16_t> ringBuffer; 
		int capacity; 
		int size; 
		int head; 
		int tail; 
};


#endif  // RINGBUFFER_H_
