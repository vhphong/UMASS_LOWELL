/***********************************************************************************/
/* main.cpp                   		   		               		                                                       */
/* Yoo Min Cha                 									   */
/* RingBuffer								                                                   */
/* Professor Martin									   */
/* 16 March 2014 									   */	
/***********************************************************************************/

#include "RingBuffer.hpp"

using namespace std;

int main()
{
   RingBuffer rb1(2);
   //RingBuffer rb2(0);
   rb1.enqueue(5);
   rb1.enqueue(2);
   cout << "is empty = " << rb1.isEmpty() << endl;
   cout << "is full = "<< rb1.isFull() << endl;
   //rb1.enqueue(3);
   rb1.dequeue();
   cout << "peek at first item = " << rb1.peek() << endl;
   rb1.dequeue();
   //rb1.dequeue();
   cout << "is empty = " << rb1.isEmpty() << endl;
   cout << "size = "<< rb1.size() << endl;
   return 0;
}