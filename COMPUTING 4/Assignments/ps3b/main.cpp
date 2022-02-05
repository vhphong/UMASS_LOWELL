#include "nbody.hpp"

int main(int argc, char *argv[])
{
  	Body **Planets = new Body*[4];
	int numOfPlanets = 0;
	float scale = 0;

	double t = 0;
	double time = (double)atoi(argv[1]);
   	double DTime=(double)atoi(argv[2]);
	sf::Music music;
  	sf::Image background;
	if (!background.loadFromFile("starfield.jpg"))
	{
    		return -1;
	}


  	std::cin >> numOfPlanets >> scale;
 
  	for (int i = 0; i<numOfPlanets; i++) {
    		Planets[i] = new Body(.0, .0, .0, .0, .0, "o");
    		std::cin >> *Planets[i];
    		(*Planets[i]).setNumOfPlanets(numOfPlanets);
  	}

  	
	if (!music.openFromFile("music.ogg"))
	{
    		return -1;
	}
	music.setLoop(true);
	music.play();
  	sf::Vector2u size = background.getSize();
  	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "The Solar System!");
	sf::Texture texture;
	texture.loadFromImage(background);
  	sf::Sprite sprite;
  	sprite.setTexture(texture);

	while (window.isOpen()) 
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
		}
		if(t<time)
		{
			window.clear();
			window.draw(sprite);
			(*Planets[0]).step(DTime,Planets,0);
 
			//drawing planets
			for (int i=0; i<numOfPlanets; i++)
			{
				(*Planets[i]).updatePosition(scale, size.x*1/2, size.y*1/2);
				window.draw(*Planets[i]);
			}
			t += DTime;
		}	
		window.display();  
	} // end while
	return 0;
} // end main
