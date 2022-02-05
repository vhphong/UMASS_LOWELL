#include "nbody.hpp"

int main(int argc, char *argv[])
{
  	Body **Planets = new Body*[4];
	int numOfPlanets= 0;
	double scale = 0;
	double t = 0;
	double time = (double)atoi(argv[1]);
   	double DTime=(double)atoi(argv[2]);
	sf::Music music;
  	sf::Image background;
	
	//planets.txt is the input file
  	std::cin >> numOfPlanets >> scale;
 
  	for (int i = 0; i<numOfPlanets; i++) {
    		Planets[i]= new Body(0.0,0.0,0.0,0.0,0.0,"o");
    		std::cin >> *Planets[i];
    		(*Planets[i]).setnum_planets(numOfPlanets);
  	}

  	if (!background.loadFromFile("starfield.jpg"))
	{
    		return -1;
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
  	sf::Sprite sprite;
  	texture.loadFromImage(background);
  	sprite.setTexture(texture);

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
			window.close();
		}
		if(t<time) {
			window.clear();
			window.draw(sprite);
			(*Planets[0]).step(DTime,Planets,0);
 
			//drawing the planets
			for (int i=0; i<numOfPlanets; i++)
			{
				(*Planets[i]).updatePosition(scale, size.x/2, size.y/2);
				window.draw(*Planets[i]);
			}
			t=t+DTime;
		}	
		window.display();  
	}
	return 0;
}
