#include <vector>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <map>
#include <string>
#include "MarkovModel.hpp"
using std::string;

// create a Markov model of order k from given text
// Assume that text has length at least k.
MarkovModel::MarkovModel(std::string text, int k)
{
	strOfChar = text;
	_order = k;
	if ((unsigned) _order >= text.length())
	{
		throw std::runtime_error("k is larger than the length of text");
	}
	for (unsigned i = 0; i < text.size(); i++)
	{
		if (ch.find(text.at(i)) == std::string::npos) {
			ch.push_back(text.at(i));
		}
	}
	for (unsigned i = 0; i < text.size(); i++) {
		std::string cha1, cha2;
		for (unsigned j = i; j < i + k; j++)
		if (j < text.size()) {
			cha1.push_back(text[j]);
		}
		else {
			cha1.push_back(text[j - text.size()]);
		}
		if (kk.end() != kk.find(cha1)) {
			kk[cha1] += 1;
		}
		else {
			kk[cha1] = 1;
		}
		for (unsigned j = 0; j < strOfChar.size(); j++)
			if (kk.end() == kk.find(cha1 + strOfChar[j])) {
				kk[cha1 + strOfChar[j]] = 0;
			}
		for (unsigned j = i; j < i + k + 1; j++)
		if (j >= text.size()) {
			cha2.push_back(text[j - text.size()]);
		}
		else {
			cha2.push_back(text[j]);
		}
		kk[cha2] += 1;
	}
}

// returns order k of Markov model
int MarkovModel::order() 
{
return _order;
}

// returns number of occurrences of kgram in text
// (throw an exception if kgram is not of length k)
int MarkovModel::freq(std::string kgram)
{
	if (kgram.size() == (unsigned)_order) {
		if (_order != 0) {
			return kk[kgram];
		} 
		else {
			return strOfChar.size();
		}
	} 
	else {
		throw std::runtime_error("kgram is not of length k");
	}
}

// returns number of times that character c follows kgram
// if order=0, return num of times char c appears
// (throw an exception if kgram is not of length k)
int MarkovModel::freq(std::string kgram, char c)
{
	if (kgram.size() == (unsigned)_order)
	{
		if (_order == 0) {
			int num = 0;
			for (unsigned i = 0; i < strOfChar.size(); i++) {
				if (strOfChar[i] == c) {
					num++;
				}
			}
			return num;
		}
		else {
			return kk[kgram + c];
		}
		return 0;
	}
	else
	{
		throw std::runtime_error("kgram is not of length k");
	}
}

// random character following given kgram
// (Throw an exception if kgram is not of length k.
//  Throw an exception if no such kgram.)
char MarkovModel::randk(std::string kgram) 
{
	if (kgram.length() == (unsigned)_order) {
		if (freq(kgram) != 0) {
			std::string temp;
			for (unsigned i = 0 ; i <strOfChar.size() ; i++) {
				for (int j = 0; j < kk[kgram + strOfChar[i]]; j++) {
					temp.push_back(strOfChar[i]);
				}
			}
			return temp[rand() % temp.size()];
		}
		else {
			throw std::runtime_error("can not find kgram");
		}
	}
	else {
		throw std::runtime_error("kgram is not of length k");
	}
}

// generate a string of length T characters
// by simulating a trajectory through the corresponding
// Markov chain.  The first k characters of the newly
// generated string should be the argument kgram.
// Throw an exception if kgram is not of length k.
// Assume that T is at least k.
string MarkovModel::gen(std::string kgram, int T) 
{
	std::string output = kgram, str;
	if (kgram.length() == (unsigned)order()) {
		while ((unsigned) T > output.length()) {
			string temp(1, randk(kgram));
			output.append(temp);
			if (_order > 0) {
				kgram = kgram.substr(1);
			}
			str = kgram + temp;
			kgram = str;
		}
		return output;
	} else {
		throw std::runtime_error("kgram does not match order size");
	}
}

// overload the stream insertion operator and display
// the internal state of the Markov Model. Print out
// the order, the alphabet, and the frequencies of
// the k-grams and k+1-grams.
std::ostream& operator << (std::ostream& out, MarkovModel& mm) 
{
	std::map<std::string, int>::iterator kk;
	out << "kgram\tfreq\t prob" << std::endl;
	out << "----------------------" << std::endl;
	for (kk = mm.kk.begin(); kk != mm.kk.end(); ++kk) {
		if ((*kk).first.length() != (unsigned) mm._order) {
			out <<(*kk).first << "\t " <<(*kk).second;
			out << std::endl;
		}
		else {
			out << std::endl;
			out << (*kk).first <<"\t "<< (*kk).second;
			out << "\t ";
			out << (*kk).second << "/" << mm.strOfChar.size();
			out << std::endl;
		}
	}
	return out;
}
