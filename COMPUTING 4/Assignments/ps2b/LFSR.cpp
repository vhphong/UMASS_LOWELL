#include <iostream>
#include <cmath>
#include "LFSR.hpp"

LFSR::LFSR(std::string seed, int t) {
	Seed = seed;
	tap = t;
}

int LFSR::step() {
	int length = Seed.length();
	int bit = Seed[0]-'0';
	int T = Seed[length-tap-1]-'0';
	
	// (bit = bit XOR T)
	bit = (bit == T)? 0 : 1;
	
	for (int i=0; i<length-1; i++) {
		Seed[i] = Seed[i+1];
	}
	Seed[length-1] = bit+48;
	return bit;
}

int LFSR::generate(int k) {
	int number = 0;
	for (int i = k; i > 0; i--) {
	   number += step() * pow(2, i-1);
	}
	return number;
}

std::ostream& operator<<(std::ostream& out, LFSR& lsfr) {
	out << lsfr.Seed;
	return out;
}
