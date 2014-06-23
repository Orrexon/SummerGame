//MathNerd.h

#pragma once
#include <SFML\Graphics.hpp>
class MathNerd
{
public:
	//a clamp template
	template<typename CObj>
	const CObj& Clamp(const CObj& xV, const CObj& xMin, const CObj& xMax)
	{
		if (xMin>xV)	{ return xMin; }
		else if (xV>xMax){ return xMax; }
		else{ return xV; };
	};
	//MathNerd
	MathNerd(){}
	~MathNerd(){}

	const sf::Vector2f& ClosestPointOnLine(const sf::Vector2f& p_vA, const sf::Vector2f& p_vB, const sf::Vector2f& p_vPoint);

};