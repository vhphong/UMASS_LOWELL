// Copyright 2018, Dangnhi Ngo

#ifndef _HOME_DAPHNE_PS6_MARKOVMODEL_H_
#define _HOME_DAPHNE_PS6_MARKOVMODEL_H_
#include <map>
#include <string>
#include <cstdlib>

class MarkovModel {
 public:
MarkovModel(std::string text, int k);
int order();
int freq(std::string kgram);
int freq(std::string kgram, char c);
char randk(std::string kgram);
std::string gen(std::string kgram, int T);
friend std::ostream& operator <<(std::ostream& out, MarkovModel& mm);
 private:
int _order;
std::string strOfChar;
std::string ch;
std::map <std::string, int> kk;
};
#endif  // _HOME_DAPHNE_PS6_MARKOVMODEL_H_
