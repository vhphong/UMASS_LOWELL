/***********************************************************************************/
/* MarkovModel.cpp                                                                 */
/* Yoo Min Cha                                                                     */
/* Markov's Model                                                                  */
/* Professor Martin                                                                */
/* 07 April 2014                                                                   */   
/***********************************************************************************/

#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <cstring>
#include "MarkovModel.hpp"

using namespace std;

MarkovModel::MarkovModel(string text, int k):_order(k), _alphabet(text)
{
  srand(time(0));
  if (k < 0)
    throw invalid_argument("Order k must be higher than zero.");  
  if (k >= text.size())
    throw invalid_argument("Order k must be less than the length of text.");
  
  string temp = "";
  if (k>0) temp = text.substr(0,k);
  
  for (int i = k; i < text.size()+k; i++)
  {
    if (_kgrams[text[i%text.size()]].count(temp) == 0){
      kgramList.insert(temp);
      //kplusList.push_back(i);
      _kgrams[text[i%text.size()]][temp] = 1;
    } else {
      _kgrams[text[i%text.size()]][temp]++;
    }
    temp += text[i%text.size()];
    temp = temp.substr(1);
    
  }
}

int MarkovModel::order()
{
  return _order; 
}

int MarkovModel::freq(string kgram)
{
  // cout << "+" <<  kgram << "+" <<kgram.size()<<"+"<<_order<<endl;
    
  if (kgram.size() != _order)
    throw runtime_error("kgram must be the same size as k1");
  
  int ans = 0;
  for(int i=0;i<128;i++)
  {
    ans += _kgrams[i][kgram];
  }
    return ans;
}
int MarkovModel::freq(string kgram, char c)
{
  if (kgram.size() != _order)
    throw runtime_error("kgram must be the same size as k2");
  if (!_kgrams[c].count(kgram)) 
    return 0;
  else 
    return _kgrams[c][kgram];
}

char MarkovModel::randk(string kgram)
{
  if (kgram.size() != _order)
    throw runtime_error("kgram must be the same size as k3");
  int freqArr[128], total=0;
  for(int i=0;i<128;i++){
    freqArr[i] = MarkovModel::freq(kgram,i);
    total += freqArr[i];
  }
  if (total!=0){
    int ran = rand()%total+1;
  
    for(int i=0;i<128;i++){
      // cout<<"ran="<<ran<<endl;
      ran -= freqArr[i];
      if (ran<=0) {
        //cout<<"return "<<i <<" "<<freqArr[i]<<endl;
        return (char) i;
      }
    }
  } else 
      throw runtime_error("No such kgram");
  
}

string MarkovModel::gen(string kgram, int T)
{
  if (kgram.size() != _order)
    throw runtime_error("kgram must be the same size as k");
    
  string result = "";
  for(int i=0;i<T;i++){
    //cout<<kgram<<"-\n";
    char nextChar = randk(kgram);
    //cout<<"next char="<<nextChar<<endl;
    result += nextChar;
    kgram += nextChar;
    kgram = kgram.substr(1);
  }
  return result;
}
  
ostream& operator<< (ostream& out, MarkovModel& mm)
{
  out << "k-gram\tfreq" << endl;
  out << "-------------" << endl;
  for (auto it = mm.kgramList.begin(); it != mm.kgramList.end(); it++)
  {
    int a = mm.freq(*it);
    out << *it << '\t' << a << endl;
  }
  out << endl;
  out << "k+1 gram\tfreq" << endl;
  out << "---------------------" << endl;
  for (auto it = mm.kgramList.begin(); it != mm.kgramList.end(); it++)
  {
    int a;
    for(int i = 0; i < 128; i++) if ((a=mm.freq(*it, (char) (i)))>0)
    {
      out << *it << " " << (char)(i) << "\t\t" << a << endl;
    }
  }
  return out;
}