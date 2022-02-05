/**********************************************************************
Student name: Phong Hong Vo
Assignment: ps5b - GUITAR HERO: GUITARSTRING IMPLEMENTATION AND SFML AUDIO OUTPUT (PART B)
Time spent: 25 hours

/**********************************************************************
Operating System: Windows 10 64 bit and Ubuntu 18.04
CPU type: Intel Core i5-8250U @ 1.6GHz
RAM: 8GB
Editor tool: notepad++ on Windows 10 and built-in textEditor on Ubuntu 18.04

/**********************************************************************

How you implemented the ring buffer (e.g. per the Princeton guidance, or some other way)?
exactly what works or doesn't work?

/**********************************************************************

I implemented the ring buffer per the Princeton guidance. 
I completely finished with no errors detected.
   (see the attaching picture).
This result shows out no exception handling occurred. 
Besides, the program passed the requirements on creating Ring Buffer, enqueue and dequeue.

/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
 
 I had some helps from my friends. They helped me approaching the problem 
    and ways to solve it.

/**********************************************************************

void GuitarString::pluck()
{
	while (!(*RB).isEmpty())
	{
		(*RB).dequeue();
	}
	while (!(*RB).isFull())
	{
		(*RB).enqueue((sf::Int16)(rand() & 0xffff));
	}
}

My pluck() function is to pluck the guitar string: 
    (*RB).enqueue((sf::Int16)(rand() & 0xffff))

/**********************************************************************

The tic() function is to simulation one time step. I let the peek reduced halfway

void GuitarString::tic()
{
	int16_t temp = (((*RB).dequeue() + (*RB).peek()) * .5) * .996;
	(*RB).enqueue(temp);
	_time++;
}

/**********************************************************************

As I executed the program with the syntax: ./GuitarHero gstest, it showed out 
a  piano shape virtual instrument. I used the laptop keys to make note sounds.

/**********************************************************************

 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 
 **********************************************************************/
 
 I had some helps from my friends. They helped me approaching the problem 
    and ways to solve it.

/**********************************************************************
