#ifndef OCTAGON_H
#define OCTAGON_H
#include <SFML/Graphics.hpp>

using namespace std;

struct octagon {
	sf::Vector2f topL, leftUp, leftDn, downL, downR, rightDn, rightUp, topR;
};

class Octagon: public sf::Drawable {
	public:
		//Constructor that takes size and depth
		Octagon(int side, int depth);

		//Constructor that takes eight points and depth
		void oct_tree(sf::Vector2f topL, sf::Vector2f leftUp, sf::Vector2f leftDn, sf::Vector2f downL, sf::Vector2f downR, sf::Vector2f rightDn, sf::Vector2f rightUp, sf::Vector2f topR, int depth);
		void virtual draw(sf::RenderTarget &target, sf::RenderStates states) const;

	private:
		sf::Vector2f _topL, _leftUp, _leftDn, _downL, _downR, _rightDn, _rightUp, _topR;
		int _depth;
};


#endif
