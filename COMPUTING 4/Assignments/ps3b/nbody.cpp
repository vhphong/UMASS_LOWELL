#include "nbody.hpp"

Body::Body(float x,float y,float xSpeed, float ySpeed,float mass, std::string image) {}
void Body:: draw(sf::RenderTarget& target, sf::RenderStates states) const 
{
	target.draw(sprite,states);
}

void Body:: setPosition(float x, float y) 
{
  	X = x;
  	Y = y;
}

void Body::setMass(float m)
{
	mass = m;
}

float Body::getMass()
{
	return mass;
}

float Body::getX() const
{
	return X;
}

float Body::getY() const
{
	return Y;
}

void Body::setNumOfPlanets(int num)
{
	numOfPlanets = num;
}

int Body::getNumOfPlanets()
{
	return numOfPlanets;
}

std::istream& operator>> (std::istream& in, Body& planet) 
{
	  in >> planet.X
	     >> planet.Y
	     >> planet.x_speed
	     >> planet.y_speed
	     >> planet.mass
	     >> planet.Image;
	planet.imageOfPlanet.loadFromFile(planet.Image);
	planet.texture.loadFromImage(planet.imageOfPlanet);
	planet.sprite.setTexture(planet.texture);
	return in;
}

void Body::updatePosition(float scale,int window_x, int window_y)
{
	sf::Vector2u size = imageOfPlanet.getSize();
	int x = window_x - 0.5*size.x + X/scale*window_x;
	int y = window_y - 0.5*size.y + Y/scale*window_y;
	sprite.setPosition(x,y);
}

void Body::step(double time,Body **Planets, int planet)
{
  	double r, F, FX, FY;
  	for (int i=0; i<getNumOfPlanets(); i++)
    	{
      		if (planet!=i)
		{
	  		r = sqrt(pow(X-(*Planets[i]).X,2)+pow(Y-(*Planets[i]).Y,2));
	  		F = (6.67e-11)*(*Planets[i]).mass*mass/pow(r,2);
	  		FX = F*(X-(*Planets[i]).X)/r;
	  		FY = F*(Y-(*Planets[i]).Y)/r;
	  		x_speed += time*FX/mass;
	  		y_speed += time*FY/mass;
		}
    	}
  	if (planet<getNumOfPlanets()-1)
	{
    		(*Planets[planet+1]).step(time, Planets, planet+1);
	}
  	X -= time*x_speed;
  	Y -= time*y_speed;
}
