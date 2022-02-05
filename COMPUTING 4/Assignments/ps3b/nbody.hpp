#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cmath>
#include <ctime>

class Body : public sf::Drawable{
	public:
		Body(float xPos, float yPos, float x_speed, float y_speed, float mass, std::string image);
		void setPosition(float xPos, float yPos);
		void setMass(float mass);
		float getMass();
		float getX() const;
		float getY() const;
		
		void setNumOfPlanets(int num);
		int getNumOfPlanets();
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void updatePosition(float scale, int windowX, int windowY);
		friend std::istream& operator >> (std::istream& in, Body& planet);
		void step(double time, Body **Planets, int planet);
	
	private:
		float X, Y, x_speed, y_speed, mass, numOfPlanets;
		std::string Image;
		sf::Image imageOfPlanet;
		sf::Texture texture;
		sf::Sprite sprite;
};
