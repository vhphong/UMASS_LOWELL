#include "nbody.hpp"

int main(int argc, char *argv[])
{
	Body **Planets = new Body*[4];
	int numOfPlanets= 0;
	double scale = 0;
	
	//create the background image
  	sf::Image background;
  	if (!background.loadFromFile("starfield.jpg"))
	{
    		return -1;
	}
  	sf::Vector2u size = background.getSize();
  	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "The Solar System!");
  	sf::Texture texture;
  	texture.loadFromImage(background);
  	sf::Sprite sprite;
  	sprite.setTexture(texture);

  	//planets.txt is the input file
  	std::cin >> numOfPlanets >> scale;
 
  	for (int i = 0; i < numOfPlanets; i++) 
	{
    		Planets[i]= new Body(0.0,0.0,0.0,0.0,0.0,"o");
    		std::cin >> *Planets[i];
  	}	
  
  	while (window.isOpen()) 
	{
    		sf::Event event;
    		while (window.pollEvent(event)) 
		{
      			if (event.type == sf::Event::Closed)
			window.close();
    		}
    
    	window.clear();
    	window.draw(sprite);

    	//drawing the planets
    	for (int i=0; i < numOfPlanets; i++) 
	{
      		(*Planets[i]).updatePosition(scale, size.x*1/2, size.y*1/2);
      		window.draw(*Planets[i]);
    	}
    	window.display();  
  }
  return 0;
  
}
