//CircleCollider.h

#pragma once
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider(sf::Vector2f pos, float rad);

	~CircleCollider();

	virtual bool overlap(Collider* other, sf::Vector2f& offset);

private:
	float m_radius;

};