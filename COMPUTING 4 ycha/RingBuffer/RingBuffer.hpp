/***********************************************************************************/
/* RingBuffer.hpp			                                                       */
/* Yoo Min Cha          														   */
/* RingBuffer					                                                   */
/* Professor Martin																   */
/* 16 March 2014 																   */	
/***********************************************************************************/

#ifndef _RINGBUFFER_H
#define _RINGBUFFER_H

#include <SFML/System.hpp>
#include <vector>
#include <iostream>
#include <exception>
#include <stdexcept>

class RingBuffer
{
private:
   int _first;
   int _last;
   int _capacity;
   bool _full;
   std::vector<sf::Int16> ringBuff;
public:
   RingBuffer(int capacity);
   int size();
   bool isEmpty();
   bool isFull();
   void enqueue(sf::Int16 x);
   sf::Int16 dequeue();
   sf::Int16 peek();
};

#endif