/**********************************************************************
Student name: Phong Hong Vo
OS: Windows 10 and Linux
Compiler: notepad++ and text editor of Ubuntu
Hours to complete assignment: 50 hours
/**********************************************************************

* This assignment is modeling the solar system with database is read 
    from file planets.txt.
* The database includes five sets of planets (earth, mars, mercury, 
	sun and venus) of positions of x and y expect to the the Sun (x=0.0, y=0.0), 
	velocity expect to x and y, the mass the of each planet 
	and the avatar of each planet.
* In this assignment, I create an object class name Body as required. 
	Besides, I set for private variables as the instances in the public Body 's constructor.
In addition, I set objects named 'imageOfPlanet', 'texture' and 'sprite'.

/**********************************************************************
 Briefly explain the workings of the features you implemented.
 Include code excerpts.
/**********************************************************************
To construct the Body class, I initialize the constructor with six arguments as following:
   Body(float xPos, float yPos, float x_speed, float y_speed, float mass, std::string image);
I also create a virtual method named 'draw'" to determine the object of each planet.
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
Besides, I have a function named 'updatePosition' to update the position 
	of each of single planet based on the database read in.

/**********************************************************************
 *  List whatever help (if any) you received from the instructor,
 *  classmates, or anyone else.
**********************************************************************
I have some discussions with my friends and some extra references from 
	the internet for the roles of the the functions.
I also asked them for techniques of loading in the database from the outsources.
 
/**********************************************************************
*  Describe any serious problems you encountered.                    
**********************************************************************
I had many problems on reading database from outsources, loading 
	parameters to an object using >> operator.

