/***********************************************************************************/
/* LFSR.cpp			                                                   */
/* Yoo Min Cha          				        		   */
/* Linear Feedback Shift Register                                                  */
/* Professor Martin								   */
/* 02 March 2014 								   */	
/***********************************************************************************/

#include "LFSR.hpp"

using namespace std;

LFSR::LFSR(string seed, int t):
sequence(seed),
keyBit(t)
{}

int LFSR::step()
{
   int result = ((sequence[sequence.size()-keyBit-1]-'0') ^ (sequence[0] -'0'));
   char intchar = result + '0';
   string ctemp(1, intchar);
   sequence.erase(sequence.begin(), sequence.begin()+1);
   sequence.append(ctemp);
   return result;
}

int LFSR::generate(int k)
{
   int result = 0;
   for(int i = 0; i < k; i++)
   {
	  result = 2 * result + step();
	  
   }
   return result;
}

string LFSR::toString()
{
   return sequence;
}

int LFSR::getKeyBit() const
{
   return keyBit;
}

ostream& operator << (ostream &out, const LFSR &cLFSR)
{
   out << cLFSR.sequence;
   return out;
}

