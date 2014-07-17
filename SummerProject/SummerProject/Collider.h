//Collider.h

#pragma once
#include <math.h>
#include "SFML\Graphics.hpp"
#include "GameObject.h"

class Collider
{
public:
	virtual bool overlap(Collider* other, sf::Vector2f& offset) = 0;
	virtual void onCollision(Collider* other) = 0;
	virtual void setParent(GameObject* parent) = 0;
	virtual GameObject* getParent() = 0;
	virtual sf::Vector2f& getOffset() = 0;
protected:
	sf::Vector2f m_position;
	GameObject* m_parent;
	sf::Vector2f m_offset;
};