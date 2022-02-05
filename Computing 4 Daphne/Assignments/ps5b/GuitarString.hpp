// Copyright 2018 Dangnhi Ngo
#ifndef _HOME_DAPHNE_PS5B_GUITARSTRING_H_
#define _HOME_DAPHNE_PS5B_GUITARSTRING_H_
#include <stdint.h>
#include <SFML/Audio.hpp>
#include <vector>
#include "RingBuffer.hpp"

class GuitarString {
 public:
explicit GuitarString(double frequency);
explicit GuitarString(std::vector<sf::Int16> init);
void pluck();
void tic();
sf::Int16 sample();
int time();
 private:
int _time;
RingBuffer* RB;
};


#endif  // _HOME_DAPHNE_PS5B_GUITARSTRING_H_
