/**********************************************************************
 *  N-Body Simulation ps3a-readme.txt template
 **********************************************************************/

Name: Dangnhi Ngoc Ngo
OS: Linux
Text editor: getit
Hours to complete assignment: 40 hours

/**********************************************************************
 *  Briefly discuss the assignment itself and what you accomplished.
 **********************************************************************/
This assignment is to simulate the universe by reading the input text file
which contains the information for a particular universe and calculating
their positions.
Through this assignment, I have learned how to read the input file and
implement the input stream operator >> as well as use it to load parameter
data into an object. 

  /**********************************************************************
 *  Discuss one or more key algorithms, data structures, or 
 *  OO designs that were central to the assignment.
 **********************************************************************/
Data Structures: the implementation of class Body
Private members: there are 6 private variables in the public Body constructor 
along with sf:: Image, sf::Texture (to hold the sprite's image) and 
sf::Sprite object
Public members: there is a class Body constructor with 6 parameters needed
to update the position, velocity, mass and image of the planet.Also, the
virtual void method draw is used and the implementation of operator >>
for inputs. 


/**********************************************************************
 *  Briefly explain the workings of the features you implemented.
 *  Include code excerpts.
 **********************************************************************/
In the Body class, there is a constructor Body which initializes 6 
parameters: 
Body::Body(double x_pos, double y_pos, double xSpeed, double ySpeed, double mass, std::string image)

Besides, the class has another feature: sf::Drawable with a virtual
void method calle "draw":
void Body:: draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite,states);
}

The function updatePosition is reading the scale from input text file,
size.x and size.y to draw the planets in the universe.
void Body:: updatePosition(double scale, int window_x, int window_y)

I overried the input stream operator >> and used it to load parameter
data into the object.
std::istream& operator>> (std::istream& in, Body& planet)

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
 **********************************************************************/
I discussed this assignment with some friends of mine
for problems I had met during working on it. For example: the way to
implement the input stream operator >>.

/**********************************************************************
 *  Describe any serious problems you encountered.                    
 **********************************************************************/
I had problems in reading the input text file and calculating as well as
updating the position for planets.

/**********************************************************************
 *  List any other comments here.                                     
 **********************************************************************/
None
