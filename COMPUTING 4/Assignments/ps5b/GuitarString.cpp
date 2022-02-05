#include <stdint.h>
#include <math.h>
#include <vector>
#include <exception>
#include <stdexcept>
#include "GuitarString.hpp"
#include "RingBuffer.hpp"

// create a guitar string of the given frequency
// using a sampling rate of 44,100
GuitarString::GuitarString(double frequency)
{
	if (frequency < 0)
	{
		throw std::invalid_argument("capacity must be greater than zero");
	}
	else
	{
		int capacity = 44100.0/frequency + .05;
		RB = new RingBuffer(capacity);
		for (int i = 0; i < capacity; i++)
		{
			(*RB).enqueue(0);
		}
		_time = 0;
	}
}

GuitarString::GuitarString(std::vector<sf::Int16> init)
{
	if (init.size() <= 0)
	{
		throw std::invalid_argument("capacity must be greater than zero");
	}
	else
	{
		RB = new RingBuffer(init.size());
		for (unsigned i = 0; i < init.size() ; i++)
		{
			(*RB).enqueue(init.at(i));
		}
		_time = 0;
	}
}

void GuitarString::pluck()
{
	while (!(*RB).isEmpty())
	{
		(*RB).dequeue();
	}
	while (!(*RB).isFull())
	{
		(*RB).enqueue((sf::Int16)(rand() & 0xffff));
	}
}

void GuitarString::tic()
{
	int16_t temp = (((*RB).dequeue() + (*RB).peek()) * .5) * .996;
	(*RB).enqueue(temp);
	_time++;
}

sf::Int16 GuitarString::sample()
{
	return (*RB).peek();
}

int GuitarString::time()
{
	return _time;
}
