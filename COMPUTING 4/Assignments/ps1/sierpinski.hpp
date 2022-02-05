#ifndef SIERPINSKI_H
#define SIERPINSKI_H
#include <SFML/Graphics.hpp>

using namespace std;

struct triangle {
	sf::Vector2f top, left, right;
};

class Sierpinski: public sf::Drawable {
	public:
		//Constructor that takes size and depth
		Sierpinski(int side, int depth);

		//Constructor that takes three points and depth
		void sierpinski_tree(sf::Vector2f top, sf::Vector2f left, sf::Vector2f right, int depth);
		void virtual draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		sf::Vector2f _top, _left, _right;
		int _depth;
};

#endif