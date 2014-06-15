//BoxCollider.h

#pragma once
#include "Collider.h"

class BoxCollider : public Collider
{
public:

	BoxCollider(sf::Vector2f pos, sf::Vector2f ext);
	~BoxCollider(){};

	bool overlap(Collider* other, sf::Vector2f& offset);

private:
	sf::Vector2f m_extention;
};