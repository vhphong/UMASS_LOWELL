#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <vector>
#include <cmath>
#include "GuitarString.hpp"
#define CONCERT_A 440.0
#define SAMPLES_PER_SEC 44100

std::vector<sf::Int16> makeSamplesFromString(GuitarString* gs)
{
	std::vector<sf::Int16> samples;
	gs->pluck();
	int duration = 8;  // seconds
	int i;
	for (i= 0; i < SAMPLES_PER_SEC * duration; i++) {
	gs->tic();
	samples.push_back(gs->sample());
	}
	return samples;
}

int main()
{
	sf::Image image;
	if (!image.loadFromFile("keyboard.png"))
	{
		return -1;
	}
	sf::Vector2u size = image.getSize();
	sf::RenderWindow window(sf::VideoMode(size.x, size.y), "Guitar Hero");
	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	std::vector<std::vector<sf::Int16> > Samples;
	std::vector<sf::SoundBuffer> SoundBuffers;
	std::vector<sf::Sound> Sounds;
	Samples.reserve(37);
	SoundBuffers.resize(37);
	Sounds.resize(37);

	for (double i = 0.0; i < 37; i++)
	{
		GuitarString gs(CONCERT_A * pow(2, (i-24)/12.0));
		Samples.push_back(makeSamplesFromString(&gs));
		if (!(SoundBuffers[i]).loadFromSamples(&Samples[i][0], Samples[i].size(), 2, SAMPLES_PER_SEC))
			throw std::runtime_error("sf::SoundBuffer: failed to load from samples.");
		Sounds[i].setBuffer(SoundBuffers[i]);
	}

	char keyboard[] = "q2we4r5ty7u8i9op-[=zxdcfvgbnjmk,.;/' ";

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			window.close();
			for (int i = 0; i < 37; i++)
			{
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode  == (unsigned)keyboard[i])
					{
						Sounds[i].play();
					}
				}
			}  // end for loop
			window.clear();
			window.draw(sprite);
			window.display();
		} // end while
	} // end while
	return 0;
}  // end main
