/***********************************************************************************/
/* RingBuffer.cpp			                                           */
/* Yoo Min Cha          							   */
/* RingBuffer					                                   */
/* Professor Martin								   */
/* 16 March 2014 								   */	
/***********************************************************************************/

#include <iostream>
#include <exception>
#include <stdexcept>
#include "RingBuffer.hpp"

using namespace std;
using namespace sf;

RingBuffer::RingBuffer(int capacity):
ringBuff(capacity, 0), _first(0), _last(0), _capacity(capacity), _full(false)
{
  if(capacity < 1)
    throw invalid_argument("Capacity must be larger than zero");
}
int RingBuffer::size()
{
  return _capacity;
}
void RingBuffer::empty()
{
  _first = 0;
  _last = 0;
  _full = false;
}
bool RingBuffer::isEmpty()
{
  return !_full && (_first == _last);
}
bool RingBuffer::isFull()
{
  return _full;
}
void RingBuffer::enqueue(Int16 x)
{
  if (this->isFull())
    throw runtime_error("Ring Buffer is full!");
  ringBuff[_last] = x;
  ++_last;
  if (_last == this->size()) _last = 0;
  if (_last == _first) _full = true;
}
Int16 RingBuffer::dequeue()
{
  if (this->isEmpty())
    throw runtime_error("Ring Buffer is empty!");
  Int16 x = ringBuff[_first];
  ++_first;
  if (_first == this->size()) _first = 0;
  if (_full) _full = false;
  return x;
}
Int16 RingBuffer::peek()
{
  if(isEmpty())
    throw runtime_error("Ring Buffer is empty!");
  return ringBuff[_first];
}