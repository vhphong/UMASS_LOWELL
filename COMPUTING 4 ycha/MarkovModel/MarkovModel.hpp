/***********************************************************************************/
/* MarkovModel.hpp                                                                 */
/* Yoo Min Cha                                                                     */
/* Markov's Model                                                                  */
/* Professor Martin                                                                */
/* 07 April 2014                                                                   */   
/***********************************************************************************/

#ifndef _MARKOVS_HPP
#define _MARKOVS_HPP

#include <cstring>
#include <stdexcept>
#include <exception>
#include <map>
#include <set>

class MarkovModel {
  
public:
  MarkovModel(std::string text, int k);
  int order();
  int freq(std::string kgram);
  int freq(std::string kgram, char c);
  char randk(std::string kgram);
  std::string gen(std::string kgram, int T);
  
  friend std::ostream& operator<< (std::ostream& out, MarkovModel& mm);
  
private:
  std::set<std::string> kgramList;
  int _order;
  std::map<std::string, int> _kgrams[128];
  std::string _alphabet;
};

#endif