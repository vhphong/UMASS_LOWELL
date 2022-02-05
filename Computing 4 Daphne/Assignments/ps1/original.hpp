#ifndef HEXAGON_H
#define HEXAGON_H
#include <SFML/Graphics.hpp>

using namespace std;

struct hexagon {
	sf::Vector2f top, left1, left2, bottom, right1, right2;
};

class Hexagon: public sf::Drawable {
public:
	//Constructor that takes size and depth
	Hexagon(int side, int depth);

	//Constructor that takes six points and depth
	void hex_tree(sf::Vector2f top, sf::Vector2f left1, sf::Vector2f left2, sf::Vector2f bottom, sf::Vector2f right1, sf::Vector2f right2, int depth);
	void virtual draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	sf::Vector2f _top, _left1, _left2, _bottom, _right1, _right2;
	int _depth;
};


#endif
