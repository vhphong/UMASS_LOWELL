#ifndef GUITARSTRING_H_
#define GUITARSTRING_H_
#include <stdint.h>
#include <SFML/Audio.hpp>
#include <vector>
#include "RingBuffer.hpp"

class GuitarString {
	
	public:
		explicit GuitarString(double frequency);// create a guitar string of the given frequency
												//   using a sampling rate of 44,100
		explicit GuitarString(std::vector<sf::Int16> init); // create a guitar string with
								//   size and initial values are given by the vector
		void pluck(); // pluck the guitar string by replacing the buffer
                             //   with random values, representing white noise
		void tic(); // advance the simulation one time step
		sf::Int16 sample(); // return the current sample
		int time(); // return number of times tic was called so far
	private:
		int _time;
		RingBuffer* RB;
};


#endif  // GUITARSTRING_H_
