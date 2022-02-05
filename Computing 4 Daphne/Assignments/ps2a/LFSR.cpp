#include <iostream>
#include <cmath>
#include "LFSR.hpp"

//constructor to create LFSR with the given initial seed and tap
//it takes a String argument whose characters are a sequence of 0s and 1s
LFSR::LFSR(std::string seed, int t) {
	Seed = seed;
	tap = t;
}

//simulate one step and return the new bit as 0 or 1
int LFSR::step() {
	int length = Seed.length();
	int bit = Seed[0]-'0';
	int T = Seed[length-tap-1]-'0';
	if (bit == T) {
		bit = 0;
	} else{
		bit=1;
	}
	for (int i=0; i<length-1; i++) {
		Seed[i] = Seed[i+1];
	}
	Seed[length-1] = bit+48;
	return bit;
}

//simulate k steps and return k-bit integer
int LFSR::generate(int k) {
	int number = 0;
	for (int i=k; i>0; i--) {
		if (step()==1){
			number += pow(2, i-1);
		}
	}
	return number;
}

std::ostream& operator<<(std::ostream& out, LFSR& lsfr) {
	out << lsfr.Seed;
	return out;
}
