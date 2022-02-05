/**********************************************************************
 *  readme.txt template                                                   
 *  Plucking a Guitar String
 **********************************************************************/

Name: Dangnhi Ngoc Ngo
CS Login: dngo


Hours to complete assignment: 15 hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
This assignment requires to implement the ring buffer holding the guitar
string position data and write test functions as well as exception handling.
Simultaneously, we implement the Karplus-Strong guitar string simulation, and generate a stream of string samples for audio playback under keyboard control. 

I have known how to create the buffer, enqueue and dequeue the ring. Besidesm
we have to throw exception when it catchs the error, such as: enqueue to
a full ring or dequeue from an empty ring.
Besides, I have created the noise for the guitar string by filling the guitar string's ring buffer with random numbers over the int16_t range in the pluck()
method.

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
Along with the enqueue and dequeue I used in RingBuffer.cpp, now I have used
other functions, such as: pluck(), tic() in Guitarstring.cpp
To the pluck(), I replaced the buffer with random values to pluck the guitar string: (*RB).enqueue((sf::Int16)(rand() & 0xffff))
To the tic(), I have advanced the simulation one time step by: 
  int16_t temp = (((*RB).dequeue() + (*RB).peek())/2) * .996;
  (*RB).enqueue(temp);


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
I have used some exceptions handling in some classes, such as in the enqueue()
and dequeue() functions: 
if (isFull()) {
	throw std::runtime_error("can't enqueue to a full ring");
}
if (isEmpty()) {
	throw std::runtime_error("can't dequeue from an empty ring");
}
Besides, it also throws the exception in GuitarString(std::vector<sf::Int16> init) if the size is less than 0.
if (init.size() <= 0) {
    	throw std::invalid_argument("capacity must be greater than zero");
In addition, I have uploaded the image keyboard.png, and added the sound that is
correlative with the pressed keyboard.
for (int i = 0; i < 37; i++) {
   if (event.type == sf::Event::TextEntered) {
      if (event.text.unicode  == (unsigned)keyboard[i]) {
             Sounds[i].play();
      }
   }
}

/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not? 
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
Yes, I completed the whole assignment successfully.
When I run ./GuitarHero, it displays the keyboard image, and it plays
the sound when I press the correlative keyboard with the note.
for (double i = 0.0; i < 37; i++) {
    	GuitarString gs(CONCERT_A * pow(2, (i-24)/12.0));
  	Samples.push_back(makeSamplesFromString(&gs));
  	if (!(SoundBuffers[i]).loadFromSamples(&Samples[i][0], Samples[i].size(), 2, SAMPLES_PER_SEC))
    		throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
  		Sounds[i].setBuffer(SoundBuffers[i]);
	}

  	char keyboard[] = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";

/**********************************************************************
 *  Did you attempt the extra credit parts? Which one(s)?
 *  Successfully or not?  As a pair, or individually?
 *  If you completed the AutoGuitar, what does it play?
 **********************************************************************/
No, I did not do the extra credit part.


/**********************************************************************
 *  Does your GuitarString implementation pass the unit tests?
 *  Indicate yes or no, and explain how you know that it does or does not.
 **********************************************************************/
Yes, it passes the unit tests.
I have tested the program with the GSTest.cpp and it printed out the result
correctly with no errors.
daphne@daphne-VirtualBox:~/ps5b$ ./gstest
Running 1 test case...

*** No errors detected


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
I have discussed some problems with my friends to find the solutions.


/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I had some problems when I tried to add the sound for the keyboard.


/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
None.


