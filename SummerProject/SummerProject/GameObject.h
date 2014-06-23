//GameObject.h

#pragma once
#include "SFML\Graphics.hpp"

class Collider;
class BoxCollider;
class CircleCollider;

class GameObject
{
public:

	virtual void onCollision(GameObject* other) = 0;
	virtual void update(float deltatime) = 0;
	virtual Collider* getCollider() = 0;
	virtual bool isDead() = 0;
protected:
	std::string m_type;
	sf::Vector2f m_position;
	bool m_dead;
	//Collider* m_collider;
	/*BoxCollider* m_boxCollider;
	CircleCollider* m_circleCollider;*/
};