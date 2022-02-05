#ifndef RINGBUFFER_H_
#define RINGBUFFER_H_

#include <stdint.h>

class RingBuffer
{
	public:
		explicit RingBuffer(int capacity);
		int size();
		bool isEmpty();
		bool isFull();
		void enqueue(int16_t x);
		int16_t dequeue(), peek(), *ringBuffer;
	private:
		int Capacity;
		int _size;
		int head, tail;
};

#endif  // RINGBUFFER_H_
