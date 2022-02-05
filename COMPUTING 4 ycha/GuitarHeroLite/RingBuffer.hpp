/***********************************************************************************/
/* RingBuffer.hpp			                                                       */
/* Yoo Min Cha          														   */
/* RingBuffer					                                                   */
/* Professor Martin																   */
/* 16 March 2014 																   */	
/***********************************************************************************/

#ifndef _RINGBUFFER_HPP
#define _RINGBUFFER_HPP

#include <SFML/System.hpp>
#include <vector>

class RingBuffer
{
private:
  int time;
  int _first;
  int _last;
  int _capacity;
  bool _full;
  std::vector<sf::Int16> ringBuff;
public:
  RingBuffer(int capacity);
  int size();
  void empty();
  bool isEmpty();
  bool isFull();
  void enqueue(sf::Int16 x);
  sf::Int16 dequeue();
  sf::Int16 peek();
};

#endif