//CircleCollider.h

#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(){}
	CircleCollider(sf::Vector2f pos, float rad);

	~CircleCollider();

	virtual bool overlap(Collider* other, sf::Vector2f& offset);
	virtual void onCollision(Collider* other);
	virtual void setParent(GameObject* parent) { m_parent = parent; }
	virtual GameObject* getParent() { return m_parent; }

	void setPosition(sf::Vector2f pos) { m_position = pos; }
	float getRadius() { return m_radius; }

private:
	float m_radius;

};