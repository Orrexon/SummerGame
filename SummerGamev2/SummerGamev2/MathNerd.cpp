//MathNerd.cpp
#include "stdafx.h"
//#include "MathNerd.h"

const sf::Vector2f& MathNerd::ClosestPointOnLine(const sf::Vector2f& p_vA, const sf::Vector2f& p_vB, const sf::Vector2f& p_vPoint)
{
	// Calculate unit vector from A->B
	sf::Vector2f vU = p_vB - p_vA;//former u
	float fLength = sqrt(vU.x*vU.x + vU.y*vU.y);
	vU /= fLength;

	// Vector from A->Point
	sf::Vector2f vAPoint = p_vPoint - p_vA;

	// Dot product between vU and vAPoint
	float fDot = vU.x*vAPoint.x + vU.y*vAPoint.y;

	// Length between two points that define the line
	fLength = sqrt(pow((p_vA.x - p_vB.x), 2) + pow((p_vA.y - p_vB.y), 2));

	// Clamp values
	fDot = Clamp(fDot, 0.0f, fLength);

	return sf::Vector2f(vU.x*fDot + p_vA.x, vU.y*fDot + p_vA.y);
}