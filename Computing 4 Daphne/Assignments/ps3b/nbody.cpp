#include "nbody.hpp"

Body::Body(double x,double y,double xSpeed, double ySpeed,double mass, std::string image) {}
void Body:: draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(sprite,states);
}

void Body:: setPosition(double x, double y) {
  	X = x;
  	Y = y;
}
void Body::setnum_planets(int num){num_planets = num;}
int Body::getnum_planets(){return num_planets;}

std::istream& operator>> (std::istream& in, Body& planet) {
  in >> planet.X
     >> planet.Y
     >> planet.X_Speed
     >> planet.Y_Speed
     >> planet.Mass
     >> planet.Image;
planet.ImageOfPlanet.loadFromFile(planet.Image);
planet.texture.loadFromImage(planet.ImageOfPlanet);
planet.sprite.setTexture(planet.texture);
return in;
}

void Body:: updatePosition(double scale,int window_x, int window_y) {
	sf::Vector2u size = ImageOfPlanet.getSize();
	int x = window_x-size.x/2+X/scale*window_x;
	int y = window_y-size.y/2+Y/scale*window_y;
	sprite.setPosition(x,y);
}

void Body:: step(double time,Body **Planets,int planet){
  	double r, F, FX, FY;
  	for (int i=0;i<getnum_planets();i++)
    	{
      		if (planet!=i)
		{
	  		r = sqrt(pow(X-(*Planets[i]).X,2)+pow(Y-(*Planets[i]).Y,2));
	  		F = (6.67e-11)*(*Planets[i]).Mass*Mass/pow(r,2);
	  		FX = F*(X-(*Planets[i]).X)/r;
	  		FY = F*(Y-(*Planets[i]).Y)/r;
	  		X_Speed = X_Speed+time*FX/Mass;
	  		Y_Speed = Y_Speed+time*FY/Mass;
		}
    	}
  	if (planet<getnum_planets()-1)
	{
    		(*Planets[planet+1]).step(time, Planets, planet+1);
	}
  	X -=(time*X_Speed);
  	Y -=(time*Y_Speed);
  
}
