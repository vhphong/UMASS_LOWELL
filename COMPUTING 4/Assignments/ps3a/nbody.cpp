#include "nbody.hpp"

Body::Body(float xPos, float yPos, float xSpeed, float ySpeed, float mass, std::string image){}

void Body::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	target.draw(sprite, states);	
}

void Body::setPosition(float x, float y){
	X = x;
	Y = y;
}

void Body::setMass(float m){
	mass = m;
}

float Body::getMass(){
	return mass;
}

float Body::getX() const{
	return X;
}

float Body::getY() const{
	return Y;
}

std::istream &operator >> (std::istream &i, Body &planet){
	i >> planet.X
	  >> planet.Y
	  >> planet.x_speed
	  >> planet.y_speed
	  >> planet.mass
	  >> planet.Image;
	
	planet.imageOfPlanet.loadFromFile(planet.Image);
	planet.texture.loadFromImage(planet.imageOfPlanet);
	planet.sprite.setTexture(planet.texture);
	
	return i;
}

void Body::updatePosition(float scale, int windowX, int windowY){
	sf::Vector2u size = imageOfPlanet.getSize();
	int x = windowX - 0.5*size.x + windowX*X/scale;
	int y = windowY - 0.5*size.y + windowY*Y/scale;
	sprite.setPosition(x,y);
}
