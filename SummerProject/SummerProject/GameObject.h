//GameObject.h

#pragma once
#include "SFML\Graphics.hpp"
#include "Collider.h"
#include "BoxCollider.h"

class GameObject
{
public:

	virtual void onCollision(GameObject* other) = 0;

protected:
	sf::Vector2f m_position;
	Collider* m_collider;
	BoxCollider* m_boxCollider;
	//CircleCollider* m_circleCollider;
};