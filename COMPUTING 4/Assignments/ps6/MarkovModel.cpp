#include <vector>
#include <exception>
#include <stdexcept>
#include <iostream>
#include <map>
#include <string>
#include "MarkovModel.hpp"
using std::string;


MarkovModel::MarkovModel(std::string text, int k){
	charString = text;
	_order = k;
	if ((unsigned) _order >= text.length())
	{
		throw std::runtime_error("k is larger than the length of text");
	}
	for (unsigned i = 0; i < text.size(); i++)
	{
		if (_alphabet.find(text.at(i)) == std::string::npos)
		{
			_alphabet.push_back(text.at(i));
		}
	}
	for (unsigned i = 0; i < text.size(); i++){
		std::string cha1, cha2;
		for (unsigned j = i; j < i + k; j++)
		if (j < text.size()){
			cha1.push_back(text[j]);
		}
		else{
			cha1.push_back(text[j - text.size()]);
		}
		if (_kgrams.end() != _kgrams.find(cha1)){
			_kgrams[cha1] += 1;
		}
		else{
			_kgrams[cha1] = 1;
		}
		for (unsigned j = 0; j < charString.size(); j++)
			if (_kgrams.end() == _kgrams.find(cha1 + charString[j]))
			{
				_kgrams[cha1 + charString[j]] = 0;
			}
		for (unsigned j = i; j < i + k + 1; j++)
			if (j >= text.size())
				cha2.push_back(text[j - text.size()]);
			else
			cha2.push_back(text[j]);
		_kgrams[cha2] += 1;
	}
}

int MarkovModel::order(){
	return _order;
}

int MarkovModel::freq(std::string kgram){
	if (kgram.size() == (unsigned)_order){
		if (_order != 0){
			return _kgrams[kgram];
		}
		else{
			return charString.size();
		}
	}
	else{
		throw std::runtime_error("kgram is not of length k");
	}
}

int MarkovModel::freq(std::string kgram, char c){
	if (kgram.size() == (unsigned)_order){
		if (_order == 0){
			int num = 0;
			for (unsigned i = 0; i < charString.size(); i++){
				if (charString[i] == c){
					num++;
				}
			}
			return num;
		}
		else{
			return _kgrams[kgram + c];
		}
		return 0;
	}
	else{
		throw std::runtime_error("kgram is not of length k");
	}
}

char MarkovModel::randk(std::string kgram){
	if (kgram.length() == (unsigned)_order){
		if (freq(kgram) != 0){
			std::string temp;
			for (unsigned i = 0 ; i <charString.size() ; i++){
				for (int j = 0; j < _kgrams[kgram + charString[i]]; j++){
					temp.push_back(charString[i]);
				}
			}
			return temp[rand() % temp.size()];
		}
		else{
			throw std::runtime_error("can not find kgram");
		}
	}
	else{
		throw std::runtime_error("kgram is not of length k");
	}
}

string MarkovModel::gen(std::string kgram, int T){
	std::string output = kgram, str;
	if (kgram.length() == (unsigned)order()){
		while ((unsigned) T > output.length()){
			string temp(1, randk(kgram));
			output.append(temp);
			if (_order > 0){
				kgram = kgram.substr(1);
			}
			str = kgram + temp;
			kgram = str;
		}
		return output;
	}
	else{
		throw std::runtime_error("kgram does not match order size");
	}
}

// (*_kgrams).first is for kgram
// (*_kgrams).second is the freq. of the appearance of charString
std::ostream& operator << (std::ostream& out, MarkovModel& mm){
	std::map<std::string, int>::iterator _kgrams;
	out << "kgram\tfreq\t prob." << std::endl;
	out << "----------------------" << std::endl;
	for (_kgrams = mm._kgrams.begin(); _kgrams != mm._kgrams.end(); ++_kgrams){
		if ((*_kgrams).first.length() != (unsigned) mm._order){
			out <<(*_kgrams).first << "\t " <<(*_kgrams).second;
			out << std::endl;
		}
		else{
			out << std::endl;
			out << (*_kgrams).first <<"\t "<< (*_kgrams).second;
			out << "\t ";
			out << (*_kgrams).second << "/" << mm.charString.size();
			out << std::endl;
		}
	}
	return out;
}
