#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

class Body : public sf::Drawable{
	public:
		Body(float xPos, float yPos, float x_speed, float y_speed, float mass, std::string image);
		void setPosition(float xPos, float yPos);
		void setMass(float mass);
		float getMass();
		float getX() const;
		float getY() const;
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
		void updatePosition(float scale, int windowX, int windowY);
		friend std::istream &operator >> (std::istream &in, Body &planet);
	
	private:
		float X, Y, x_speed, y_speed, mass;
		std::string Image;
		sf::Image imageOfPlanet;
		sf::Texture texture;
		sf::Sprite sprite;
};
