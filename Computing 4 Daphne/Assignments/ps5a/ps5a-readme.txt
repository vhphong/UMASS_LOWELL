/**********************************************************************
 *  readme.txt template                                                   
 *  Guitar Hero: RingBuffer implementation with unit tests and exceptions
 **********************************************************************/

Name: Dangnhi Ngo

Hours to complete assignment: 10 hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
This assignment requires to implement the ring buffer holding the guitar
string position data and write test functions as well as exception handling.

I have known how to create the buffer, enqueue and dequeue the ring. Besidesm
we have to throw exception when it catchs the error, such as: enqueue to
a full ring or dequeue from an empty ring.

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
The algorithms I have used for this assignment is to enqueue and dequeue
the buffer ring.
To enqueue to the ring, if the ring is not full and the size = 0, we add
the item x to the ring and it becomes the head. Otherwise, if the size is
not equal to 0, depending on the tail is 0 or not, we add the item x
to the end of the ring. The size of the ring increments.
To dequeue from the ring, if the ring is not empty, we delete the item
from the front and return its value. Simultaneously, the size decrements.


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
For this assignment, the feature is throwing the exception 
when implementing the enqueue, dequeue to the RingBuffer 
For enqueue to the ring, we should check whether the Ring is full before
implementing. If the Ring is full, we have to throw the exception.
if (isFull()) {
	throw std::runtime_error("can't enqueue to a full ring");
}

Besides, to dequeue from the ring, we have to check if the Ring is empty 
before implementing. If the ring is empty, the exception is thrown:
if (isEmpty()) {
	throw std::runtime_error("can't dequeue from an empty ring");
}


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
I completed the whole assignment successfylly.
I ran the execute file "ps5a" and the output was:
Running 3 test cases...

*** No errors detected

Therefore, I think there are no problems with my assignment.
The test.cpp file has tested all the functions: isEmpty(), isFull(), peek(),
size(), enqueue(), dequeue() and they ran successfully.


/**********************************************************************
 *  Does your RingBuffer implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
My RingBuffer implementation passes the unit tests.
The output when I ran the execute file was:
Running 3 test cases...

*** No errors detected

It means that they passed the test in creating the RingBuffer, enqueue,
dequeue,... and did not throw any exception handling.

/**********************************************************************
 *  Explain the time and space performance of your RB implementation
**********************************************************************/
As I understand about this question, the space of my RB implementation 
was performed based on the Ring Buffer created with capacity > 0 and
int16_t data type.
ringBuffer = new int16_t[Capacity];
head = Capacity-1;
tail = Capacity-1;
_size = 0; 
Everytime, we enqueue or dequeue from the ring, we adjust its size.
To enqueue to the ring when the ring is not full:
if (tail == 0) {
	tail = Capacity-1;
	ringBuffer[tail] = x;
	_size++;
} else {
	ringBuffer[tail-1] = x;
	tail--;
	_size++;
}
Besides, when dequeueing from the unempty ring:
if (head-1 < 0 && _size > 1) {
	ringBuffer[head] = 0;
	head = Capacity-1;
} else {
	ringBuffer[head] = 0;
	if (_size > 1)
	head--;
}
}
_size--;

About the time performance of my RB implementation, I spent 4 hours to 
write base codes for test.cpp, RingBuffer.hpp and the functions RingBuffer::RingBuffer(int capacity) : Capacity(capacity), 
int RingBuffer::size(), bool RingBuffer::isEmpty(),
bool RingBuffer::isFull() of RingBuffer.cpp.
The rest of time, around 4 hours for euqueue, dequeue and peek to implement
the ring. The last 2 hours were used to fix bugs and test the cases.


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
I have discussed some problems with my friends to find the solutions.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I had the struggles how to dequeue from the ring accurately.
I had to think to many cases, such as (head-1 < 0 && _size > 1) or 
if the (_size > 1)


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
None.

