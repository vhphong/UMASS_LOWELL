#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <iostream>

class Body : public sf::Drawable
{
private:
  	double X;
  	double Y;
  	double X_Speed;
  	double Y_Speed;
  	double Mass;
  	double num_planets;
  	std::string Image;
  	sf::Texture texture;
  	sf::Image ImageOfPlanet;
  	sf::Sprite sprite;
public:
  	Body(double x,double y,double xSpeed, double ySpeed,double mass, std::string image);
  	void setPosition(double x_pos, double y_pos);
  	void setnum_planets(int num);
  	int getnum_planets();
   	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
  	void updatePosition(double scale,int window_x, int window_y);
  	friend std::istream& operator>> (std::istream& in, Body& planet);
  	void step(double time,Body **Planets,int planet);
};
