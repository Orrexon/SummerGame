//BoxCollider.h

#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:

	BoxCollider(sf::Vector2f pos, sf::Vector2f ext);
	~BoxCollider(){};

	virtual bool overlap(Collider* other, sf::Vector2f& offset);
	virtual void onCollision(Collider* other);

	sf::Vector2f& GetExtention() { return m_extention; }

private:
	sf::Vector2f m_extention;
};