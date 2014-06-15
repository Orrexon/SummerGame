//GameObject.h

#pragma once
#include "SFML\Graphics.hpp"
#include "Collider.h"

class GameObject
{
public:

	//virtual ~GameObject() = 0;

protected:
	sf::Vector2f m_position;
	Collider* m_collider;
};