/***********************************************************************************/
/* GuitarString.hpp                                                                */
/* Yoo Min Cha                                                                     */
/* GuitarString                                                                    */
/* Professor Martin                                                                */
/* 28 March 2014                                                                   */   
/***********************************************************************************/

#ifndef _GuitarString_HPP
#define _GuitarString_HPP

#include <SFML/System.hpp>
#include <vector>

#include "RingBuffer.hpp"

class GuitarString
{
private:
  RingBuffer* _rb;
  int _time;
public:
  GuitarString(double frequency);
  GuitarString(std::vector<sf::Int16> init);
  ~GuitarString();
  void pluck();
  void tic();
  sf::Int16 sample();
  int time();
};

#endif
