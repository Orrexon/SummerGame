//Collider.h

#pragma once
#include <math.h>
#include "SFML\Graphics.hpp"

class Collider
{
public:

	//virtual ~Collider() = 0;

	virtual bool overlap(Collider* other, sf::Vector2f& offset) = 0;

protected:
	sf::Vector2f m_position;
};