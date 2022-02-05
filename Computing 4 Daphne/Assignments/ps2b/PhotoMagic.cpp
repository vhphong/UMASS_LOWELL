#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "LFSR.hpp"

sf::Image createOutput(sf::Image image, LFSR lfsr) 
{
	sf::Vector2u size = image.getSize();
  	sf::Color p;
  	for (unsigned x = 0; x < size.x; x++)
    	{
      		for (unsigned y = 0; y < size.y; y++)
		{
	  		p = image.getPixel(x, y);
	  		p.r ^= lfsr.generate(8);
	  		p.g ^= lfsr.generate(8);
	  		p.b ^= lfsr.generate(8);
	  		image.setPixel(x, y, p);
		}
    	}
  	return image;
}

int main(int argc, char *argv[]) 
{
  	sf::Image input;
  	if (!input.loadFromFile(argv[1]))
	{
    		return -1;
	}
  	
	sf::Image output;
  	if (!output.loadFromFile(argv[1]))
	{
    		return -1;
	}
  
	LFSR lfsr(argv[3],atoi(argv[4]));
  	output = createOutput(output, lfsr);
  	
	sf::Vector2u size = input.getSize();
	//create window1 for Input
  	sf::RenderWindow window1(sf::VideoMode(size.x, size.y), "Input");
	//create window2 for Output
  	sf::RenderWindow window2(sf::VideoMode(size.x, size.y), "Output");
	
	//create texture and sprite for input
  	sf::Texture texture;
  	texture.loadFromImage(input);
  	sf::Sprite sprite;
  	sprite.setTexture(texture);
	
	//create texture and sprite for output
  	sf::Texture output_texture;
  	output_texture.loadFromImage(output);
  	sf::Sprite output_sprite;
  	output_sprite.setTexture(output_texture);

	while (window1.isOpen() && window2.isOpen()) {                         
    		sf::Event event;
   		while (window1.pollEvent(event)) {
      			if (event.type == sf::Event::Closed)
        		window1.close();
    		}
    		while (window2.pollEvent(event)) {
      			if (event.type == sf::Event::Closed)
        		window2.close();
    		}
    		window1.clear();
    		window1.draw(sprite);
    		window1.display();
    		window2.clear();
    		window2.draw(output_sprite);
    		window2.display();
  	}
  	
	//create output file
  	if (!output.saveToFile(argv[2]))
    		return -1;
  	return 0;
}
