#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "sierpinski.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	 if(argc < 3)
	 {
		  cout<<"sierpinski [recursion-depth] [side-length]"<<endl;
		  return -1;
	 }
	 int depth = atoi(argv[1]);
	 int side = atoi(argv[2]);
	 Sierpinski s(side,depth);
	 
	 //const float pi = std::acos(-1.0);
	 sf::RenderWindow
		  window(sf::VideoMode(side,(int)(0.5*sqrt(3.)*(float)side)), "Sierpinski!");
	 window.setVerticalSyncEnabled(true);
	 window.setFramerateLimit(1);

	 while(window.isOpen())
	 {
		  sf::Event event;
		  while(window.pollEvent(event))
		  {
		  	if(event.type == sf::Event::Closed)
				window.close();
		  }
		  window.clear();
		  window.draw(s);
		  window.display();
	 }
	 return 0;
}
