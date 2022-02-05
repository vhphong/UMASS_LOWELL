#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <vector>
#include "original.hpp"

using namespace std;

vector<struct octagon> vect;

Octagon::Octagon(int side,int depth): _depth(depth) {
	const float pi = std::acos(-1.0);
	float width = (int)((float)side*sin(3.*pi/8.0));
	
	int xL = (int)(width/(2.0+sqrt(2.0)));
	int xR = (int)(width/(sqrt(2.0)));
	int yU = xL;
	int yD = xR;
	
	_topL    = sf::Vector2f(xL, 0);
	_leftUp  = sf::Vector2f(0, yU);
	_leftDn  = sf::Vector2f(0, yD);
	_downL   = sf::Vector2f(xL, width);
	_downR   = sf::Vector2f(xR, width);
	_rightDn = sf::Vector2f(width, yD);
	_rightUp = sf::Vector2f(width, yU);
	_topR    = sf::Vector2f(xR, 0);
	
	if (_depth >= 1){
		struct octagon oct;
		
		oct.topL    = sf::Vector2f((_topL.x + _leftUp.x)/2, (_topL.y + _leftUp.y)/2);
		oct.leftUp  = sf::Vector2f((_leftUp.x + _leftDn.x)/2, (_leftUp.y + _leftDn.y)/2);
		oct.leftDn  = sf::Vector2f((_leftDn.x + _downL.x)/2, (_leftDn.y + _downL.y)/2);
		oct.downL   = sf::Vector2f((_downL.x + _downR.x)/2, (_downL.y + _downR.y)/2);
		oct.downR   = sf::Vector2f((_downR.x + _rightDn.x)/2, (_downR.y + _rightDn.y)/2);
		oct.rightDn = sf::Vector2f((_rightDn.x + _rightUp.x)/2, (_rightDn.y + _rightUp.y)/2);
		oct.rightUp = sf::Vector2f((_rightUp.x + _topR.x)/2, (_rightUp.y + _topR.y)/2);
		oct.topR    = sf::Vector2f((_topR.x + _topL.x)/2, (_topR.y + _topL.y)/2);
		
		vect.push_back(oct);
		oct_tree(oct.topL, oct.leftUp, oct.leftDn, oct.downL, oct.downR, oct.rightDn, oct.rightUp, oct.topR, depth);
	}
}

void Octagon::oct_tree(sf::Vector2f topL, sf::Vector2f leftUp, sf::Vector2f leftDn, sf::Vector2f downL,sf::Vector2f downR,sf::Vector2f rightDn, sf::Vector2f rightUp, sf::Vector2f topR, int depth) {
	struct octagon oct;

	oct.topL    = sf::Vector2f((topL.x + leftUp.x)/2, (topL.y + leftUp.y)/2);
	oct.leftUp  = sf::Vector2f((leftUp.x + leftDn.x)/2, (leftUp.y + leftDn.y)/2);
	oct.leftDn  = sf::Vector2f((leftDn.x + downL.x)/2, (leftDn.y + downL.y)/2);
	oct.downL   = sf::Vector2f((downL.x + downR.x)/2, (downL.y + downR.y)/2);
	oct.downR   = sf::Vector2f((downR.x + rightDn.x)/2, (downR.y + rightDn.y)/2);
	oct.rightDn = sf::Vector2f((rightDn.x + rightUp.x)/2, (rightDn.y + rightUp.y)/2);
	oct.rightUp = sf::Vector2f((rightUp.x + topR.x)/2, (rightUp.y + topR.y)/2);
	oct.topR    = sf::Vector2f((topR.x + topL.x)/2, (topR.y + topL.y)/2);

	if (depth > 1) {
		vect.push_back(oct);
		oct_tree(oct.topL, oct.leftUp, oct.leftDn, oct.downL, oct.downR, oct.rightDn, oct.rightUp, oct.topR, depth - 1);
	}
}

void Octagon::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::ConvexShape filledOctagon;
	
	filledOctagon.setPointCount(8);
	filledOctagon.setPoint(0, _topL);
	filledOctagon.setPoint(1, _leftUp);
	filledOctagon.setPoint(2, _leftDn);
	filledOctagon.setPoint(3, _downL);
	filledOctagon.setPoint(4, _downR);
	filledOctagon.setPoint(5, _rightDn);
	filledOctagon.setPoint(6, _rightUp);
	filledOctagon.setPoint(7, _topR);
	
	filledOctagon.setFillColor(sf::Color::Yellow);
	target.draw(filledOctagon, states);

	for (unsigned int i = 0; i < vect.size(); i++) {
		filledOctagon.setPointCount(8);
		
		filledOctagon.setPoint(0, vect[i].topL);
		filledOctagon.setPoint(1, vect[i].leftUp);
		filledOctagon.setPoint(2, vect[i].leftDn);
		filledOctagon.setPoint(3, vect[i].downL);
		filledOctagon.setPoint(4, vect[i].downR);
		filledOctagon.setPoint(5, vect[i].rightDn);
		filledOctagon.setPoint(6, vect[i].rightUp);
		filledOctagon.setPoint(7, vect[i].topR);

		filledOctagon.setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255, rand() % 255));
		target.draw(filledOctagon, states);
	}
}
