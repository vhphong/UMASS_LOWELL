#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "original.hpp"

using namespace std;

vector<struct hexagon> vect;

Hexagon::Hexagon(int side,int depth): _depth(depth) {
	float width = (int)(0.5*sqrt(3.)*(float)side);
	_top = sf::Vector2f(width/2, 0);
	_left1 = sf::Vector2f(0, side/4);
	_left2 = sf::Vector2f(0, 3.0*side/4);
	_bottom = sf::Vector2f(width/2, side);
	_right1 = sf::Vector2f(width, 3.0*side/4);
	_right2 = sf::Vector2f(width, side/4);
	
	if (_depth >= 1){
		struct hexagon hex;
		hex.top = sf::Vector2f((_top.x+_left1.x)/2, (_top.y+_left1.y)/2);
		hex.left1 = sf::Vector2f((_left1.x+_left2.x)/2,(_left1.y+_left2.y)/2);
		hex.left2 = sf::Vector2f((_left2.x+_bottom.x)/2,(_left2.y+_bottom.y)/2);
		hex.bottom = sf::Vector2f((_bottom.x+_right1.x)/2,(_bottom.y+_right1.y)/2);
		hex.right1 = sf::Vector2f((_right1.x+_right2.x)/2,(_right1.y+_right2.y)/2);
		hex.right2 = sf::Vector2f((_right2.x+_top.x)/2,(_right2.y+_top.y)/2);
		vect.push_back(hex);
		hex_tree(hex.top, hex.left1, hex.left2, hex.bottom, hex.right1, hex.right2, depth);
	}
}

void Hexagon::hex_tree(sf::Vector2f top, sf::Vector2f left1, sf::Vector2f left2, sf::Vector2f bottom,sf::Vector2f right1,sf::Vector2f right2, int depth) {
	struct hexagon hex;

	hex.top = sf::Vector2f((top.x+left1.x)/2,(top.y+left1.y)/2);
	hex.left1 = sf::Vector2f((left1.x+left2.x)/2,(left1.y+left2.y)/2);
	hex.left2 = sf::Vector2f((left2.x+bottom.x)/2,(left2.y+bottom.y)/2);
	hex.bottom = sf::Vector2f((bottom.x+right1.x)/2,(bottom.y+right1.y)/2);
	hex.right1 = sf::Vector2f((right1.x+right2.x)/2,(right1.y+right2.y)/2);
	hex.right2 = sf::Vector2f((right2.x+top.x)/2,(right2.y+top.y)/2);

	if (depth > 1) {
		vect.push_back(hex);
		hex_tree(hex.top, hex.left1, hex.left2, hex.bottom, hex.right1, hex.right2, depth - 1);
	}
}

void Hexagon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::ConvexShape filledHexagon;

	filledHexagon.setPointCount(6);
	filledHexagon.setPoint(0, _top);
	filledHexagon.setPoint(1, _left1);
	filledHexagon.setPoint(2, _left2);
	filledHexagon.setPoint(3, _bottom);
	filledHexagon.setPoint(4, _right1);
	filledHexagon.setPoint(5, _right2);
	filledHexagon.setFillColor(sf::Color::Yellow);
	target.draw(filledHexagon, states);

	for (unsigned int i = 0; i < vect.size(); i++) {
		filledHexagon.setPointCount(6);
		filledHexagon.setPoint(0, vect[i].top);
		filledHexagon.setPoint(1, vect[i].left1);
		filledHexagon.setPoint(2, vect[i].left2);
		filledHexagon.setPoint(3, vect[i].bottom);
		filledHexagon.setPoint(4, vect[i].right1);
		filledHexagon.setPoint(5, vect[i].right2);

		filledHexagon.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
		target.draw(filledHexagon, states);
	}
}
