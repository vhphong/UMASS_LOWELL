/***********************************************************************************/
/* LFSR.hpp                                     	                           */
/* Yoo Min Cha          				        		   */
/* Linear Feedback Shift Register                                                  */
/* Professor Martin								   */
/* 02 March 2014	 							   */	
/***********************************************************************************/

#ifndef _LFSR_H
#define _LFSR_H

#include <cstring>
#include <deque>
#include <iostream>
#include <cstdlib>

class LFSR
{
private:  
   int keyBit;
   std::string sequence;
public:
   LFSR(std::string seed, int t);
   int step();
   int generate(int k);
   std::string toString();
   int getKeyBit() const;
   friend std::ostream& operator << (std::ostream &out, const LFSR &cLFSR);
};

#endif