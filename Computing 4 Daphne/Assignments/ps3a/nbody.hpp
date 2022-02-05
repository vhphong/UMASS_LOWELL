#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

class Body : public sf::Drawable
{
	private:
  		double X;
  		double Y;
  		double xSpeed;
  		double ySpeed;
  		double Mass;
  		std::string Image;
		sf::Image ImageOfPlanet;
  		sf::Texture texture;		
  		sf::Sprite sprite;

	public:
  		Body(double x_pos, double y_pos, double xSpeed, double ySpeed, double mass, std::string image);
  		void setPosition(double x_pos, double y_pos);
  		void setMass(double mass);
		double getMass();
  		double get_x() const;
  		double get_y() const;  		
   		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  		void updatePosition(double scale,int window_x, int window_y);
  		friend std::istream& operator>> (std::istream& in, Body& planet); 
};
