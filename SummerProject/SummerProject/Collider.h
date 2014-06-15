//Collider.h

#pragma once
#include <math.h>
#include "SFML\Graphics.hpp"

class Collider
{
public:

	virtual bool overlap(Collider* other, sf::Vector2f& offset) = 0;
	virtual void onCollision(Collider* other) = 0;

protected:
	sf::Vector2f m_position;
	//template<class object*> parent;
};