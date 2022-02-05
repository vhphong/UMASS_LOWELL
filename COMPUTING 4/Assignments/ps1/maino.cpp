#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "original.hpp"

using namespace std;

int main(int argc, char* argv[])
{
	 if(argc < 3)
	 {
		  cout<<"Octagon [recursion-depth] [side-length]"<<endl;
		  return -1;
	 }
	 int depth = atoi(argv[1]);
	 int side = atoi(argv[2]);
	 Octagon s(side, depth);
	 
	 const float pi = std::acos(-1.0);
	 sf::RenderWindow
		  window(sf::VideoMode((int)(float)(side*sin(3.*pi/8.0)), (int)(float)(side*sin(3.*pi/8.0))), "Octagon");

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
