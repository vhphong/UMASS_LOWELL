#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "sierpinski.hpp"

using namespace std;

vector<struct triangle> vect;

Sierpinski::Sierpinski(int side, int depth): _depth(depth) {
	_top = sf::Vector2f(side / 2.0, 0);
	float height = 0.5 * sqrt(3.) * float(side);
	_left = sf::Vector2f(0, height);
	_right = sf::Vector2f(side - 1, height);
	
	if (_depth >= 1){
		struct triangle tri;
		tri.top   = sf::Vector2f((_left.x + _right.x)/2, _left.y);
		tri.right = sf::Vector2f((_top.x + _right.x)/2, _right.y/2);
		tri.left  = sf::Vector2f(_right.x/4, _right.y/2);
		vect.push_back(tri);
		sierpinski_tree(tri.top, tri.left, tri.right, _depth);
	}
}

void Sierpinski::sierpinski_tree(sf::Vector2f top, sf::Vector2f left, sf::Vector2f right, int depth) {
	struct triangle tri1;
	struct triangle tri2;
	struct triangle tri3;

	tri1.top  = sf::Vector2f((right.x-left.x)/2 + left.x, right.y);
	tri1.right = sf::Vector2f(right.x-(right.x-left.x)/4, left.y - (top.y-left.y)/2);
	tri1.left = sf::Vector2f( (right.x-left.x)/4 + left.x, left.y - (top.y-left.y)/2);

	tri2.top  = sf::Vector2f(top.x - (right.x-left.x)/2, top.y);
	tri2.right = sf::Vector2f(left.x + (right.x-left.x)/4, (top.y-left.y)/2 + left.y);
	tri2.left = sf::Vector2f(left.x - (right.x-left.x)/4, (top.y-left.y)/2 + left.y);

	tri3.top  = sf::Vector2f(top.x + (right.x-left.x)/2, top.y);
	tri3.right = sf::Vector2f(right.x + (right.x-left.x)/4, (top.y-left.y)/2 + left.y);
	tri3.left = sf::Vector2f(right.x - (right.x-left.x)/4, (top.y-left.y)/2 + left.y);

	if (depth > 1) {
		vect.push_back(tri1);
		vect.push_back(tri2);
		vect.push_back(tri3);

		sierpinski_tree(tri1.top, tri1.left, tri1.right, depth - 1);
		sierpinski_tree(tri2.top, tri2.left, tri2.right, depth - 1);
		sierpinski_tree(tri3.top, tri3.left, tri3.right, depth - 1);
	}
}

void Sierpinski::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::ConvexShape filledTriangle;

	filledTriangle.setPointCount(3);
	filledTriangle.setPoint(0, _left);
	filledTriangle.setPoint(1, _right);
	filledTriangle.setPoint(2, _top);
	filledTriangle.setFillColor(sf::Color::Red);
	target.draw(filledTriangle, states);

	for (unsigned int i = 0; i < vect.size(); i++) {
		filledTriangle.setPointCount(3);
		filledTriangle.setPoint(0, vect[i].top);
		filledTriangle.setPoint(1, vect[i].left);
		filledTriangle.setPoint(2, vect[i].right);
		filledTriangle.setFillColor(sf::Color::Black);
		target.draw(filledTriangle, states);
	}
}
