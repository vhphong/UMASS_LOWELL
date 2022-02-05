/***********************************************************************************/
/* GuitarString.cpp                                                                */
/* Yoo Min Cha                                                                     */
/* GuitarString                                                                    */
/* Professor Martin                                                                */
/* 16 March 2014                                                                   */   
/***********************************************************************************/

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>
#include "GuitarString.hpp"

using namespace std;
using namespace sf;

GuitarString::GuitarString(double frequency)
{
  _time = 0;
  _rb = new RingBuffer(frequency);
}
GuitarString::GuitarString(vector<Int16> init)
{
  _rb = new RingBuffer(init.size());
  for (unsigned int i = 0; i < init.size(); i++)
    _rb->enqueue(init[i]);
}
GuitarString::~GuitarString()
{
}
void GuitarString::pluck()
{
  _rb->empty();
  while (!_rb->isFull())
  {
    _rb->enqueue((Int16)(rand() & 0xffff));
  }
}
void GuitarString::tic()
{
  Int16 x = _rb->dequeue();
  double decay = .996*.5;
  _rb->enqueue((x+_rb->peek()) * decay);
  _time++;
}
Int16 GuitarString::sample()
{
  return (_rb->peek());
}
int GuitarString::time()
{
  return _time;
}