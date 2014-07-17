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
	virtual sf::Vector2f& getOffset(){ return m_offset; }

	void setPosition(sf::Vector2f pos) { m_position = pos; }
	float getRadius() { return m_radius; }
	sf::Vector2f& getPosition() { return m_position; }

private:
	float m_radius;

};