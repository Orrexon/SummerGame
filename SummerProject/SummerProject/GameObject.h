//GameObject.h

#pragma once
#include "SFML\Graphics.hpp"

class Collider;
class BoxCollider;

class GameObject
{
public:

	virtual void onCollision(GameObject* other) = 0;
	virtual void update(float deltatime) = 0;
	virtual BoxCollider* getBoxCollider() = 0;
protected:
	std::string m_type;
	sf::Vector2f m_position;
	Collider* m_collider;
	BoxCollider* m_boxCollider;
	//CircleCollider* m_circleCollider;
};