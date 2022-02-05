#include <stdint.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include "RingBuffer.hpp"

// create an empty ring buffer, with given max capacity
RingBuffer::RingBuffer(int capacity) : Capacity(capacity)
{
	if (Capacity <= 0)
	{
		throw std::invalid_argument("capacity must be greater than zero.");
	}
	else
	{
		ringBuffer = new int16_t[Capacity];
		head = Capacity-1;
		tail = Capacity-1;
		_size = 0;
	}
}

// return number of items currently in the buffer
int RingBuffer::size()
{
	return _size;
}

// is the buffer empty (size equals zero)?
bool RingBuffer::isEmpty()
{
	if (_size == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// is the buffer full  (size equals capacity)?
bool RingBuffer::isFull()
{
	if (_size == Capacity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

// add item x to the end
void RingBuffer::enqueue(int16_t x)
{
	if (isFull())
	{
		throw std::runtime_error("can't enqueue to a full ring");
	}
	else if (_size == 0) 
	{
		ringBuffer[head] = x;
		_size++;
	}
	else
	{
		if (tail == 0)
		{
			tail = Capacity-1;
			ringBuffer[tail] = x;
			_size++;
		}
		else
		{
			ringBuffer[tail-1] = x;
			tail--;
			_size++;
		}
	}
}

// delete and return item from the front
int16_t RingBuffer::dequeue()
{
	int16_t temp = ringBuffer[head];
	if (isEmpty())
	{
		throw std::runtime_error("can't dequeue from an empty ring");
	}
	else
	{
		if (head-1 < 0 && _size > 1)
		{
			ringBuffer[head] = 0;
			head = Capacity-1;
		}
		else
		{
			ringBuffer[head] = 0;
			if (_size > 1)
			head--;
		}
	}
	_size--;
	return temp;
}

// return (but do not delete) item from the front
int16_t RingBuffer::peek()
{
	if (isEmpty())
	{
		throw std::runtime_error("The ring is empty");
	}
	return ringBuffer[head];
}
