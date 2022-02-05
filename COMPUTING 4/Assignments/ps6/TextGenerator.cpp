#include <string>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <cstdlib>
#include "MarkovModel.hpp"

int main(int argc, char* argv[])
{
	int k = atoi(argv[1]);
	int T = atoi(argv[2]);
	std::string kgram;
	std::cin >> kgram;
	MarkovModel mm(kgram, k);
	kgram = kgram.substr(0, k);
	std::cout << mm.gen(kgram, T) << std::endl;
	std::cout << mm << std::endl;
	return 0;
}
