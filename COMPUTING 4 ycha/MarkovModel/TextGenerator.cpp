/***********************************************************************************/
/* TextGenerator.cpp                                                               */
/* Yoo Min Cha                                                                     */
/* Markov's Model                                                                  */
/* Professor Martin                                                                */
/* 07 April 2014                                                                   */   
/***********************************************************************************/

// build with $make

#include <iostream>
#include <ctime>
#include <random>
#include <vector>
#include <cstring>
#include "MarkovModel.hpp"

using namespace std;

int main(int argc, char *argv[])
{
  int k = atoi(argv[1]);
  int T = atoi(argv[2]);
  string text = "";
  char c;
  while(scanf("%c",&c)!=EOF){
    if (c!='\n') text += c;
    }
  cout << endl;
  
  MarkovModel mm(text, k);
  cout << mm << endl;
  //cout << k<< " "<< T <<" "<<text.substr(0,k) <<endl;
  cout << "result is: ";
  cout << mm.gen(text.substr(0,k),T) << endl;
    
  return 0;
}