//BoxCollider.h

#pragma once
#include "GameObject.h"
#include "Collider.h"
#include "MathNerd.h"

class BoxCollider : public Collider
{
public:

	BoxCollider(sf::Vector2f pos, sf::Vector2f ext);
	~BoxCollider(){};

	virtual bool overlap(Collider* other, sf::Vector2f& offset);
	virtual void onCollision(Collider* other);
	virtual void setParent(GameObject* p_parent) { m_parent = p_parent; }
	virtual GameObject* getParent() { return m_parent; }

	sf::Vector2f& GetExtention() { return m_extention; }
	void SetPosition(sf::Vector2f pos) { m_position = pos; }
	sf::Vector2f& getPosition() { return m_position; }
	sf::Vector2f& getOffset() { return m_offset; }

private:
	sf::Vector2f m_extention;
};