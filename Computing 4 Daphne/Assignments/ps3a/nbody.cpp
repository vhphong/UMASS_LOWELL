#include "nbody.hpp"

Body::Body(double x_pos, double y_pos, double xSpeed, double ySpeed, double mass, std::string image) {}

void Body:: draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite,states);
}

void Body:: setPosition(double x, double y)
{
  	X = x;
  	Y = y;
}

void Body:: setMass(double mass) 
{
  	Mass = mass;
}
	
double Body::getMass() 
{
  	return Mass;
}

double Body:: get_x() const {
  	return X;
}

double Body:: get_y() const {
  	return Y;
}

std::istream& operator>> (std::istream& in, Body& planet) 
{
     	in >> planet.X
    	   >> planet.Y
     	   >> planet.xSpeed
     	   >> planet.ySpeed
     	   >> planet.Mass
     	   >> planet.Image;
	planet.ImageOfPlanet.loadFromFile(planet.Image);
	planet.texture.loadFromImage(planet.ImageOfPlanet);
	planet.sprite.setTexture(planet.texture);

	return in;
}

void Body:: updatePosition(double scale, int window_x, int window_y) {
	sf::Vector2u size = ImageOfPlanet.getSize();
	int x = window_x - size.x*1/2 + X/scale*window_x;
	int y = window_y - size.y*1/2 + Y/scale*window_y;
	sprite.setPosition(x,y);
}


