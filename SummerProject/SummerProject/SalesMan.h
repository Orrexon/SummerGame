//SalesMan.h
#pragma once
#include "GameObject.h"
#include "Bullet.h"
#include "BoxCollider.h"

class SalesMan : public GameObject
{
public:
	SalesMan(Collider* collider, sf::Vector2f position);
	~SalesMan(){}

	virtual void onCollision(GameObject* other);
	virtual void update(float deltatime);
	virtual Collider* getCollider(){ return m_boxCollider; }
	virtual bool isDead() { return m_dead; }
	virtual eTypes getEType() { return m_eType; }
	void initTestBody();
	sf::RectangleShape getRect() { return m_testBodyRect; }

private:
	BoxCollider* m_boxCollider;
	sf::RectangleShape m_testBodyRect;
};