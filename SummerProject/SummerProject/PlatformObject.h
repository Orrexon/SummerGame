//PlatformObject.h

#pragma once
#include "GameObject.h"
#include "BoxCollider.h"

class PlatformObject : public GameObject
{
public:
	PlatformObject(Collider* collider, sf::Vector2f position);
	void initTestBody();
	virtual void onCollision(GameObject* other);

	sf::RectangleShape GetRect() { return m_TestBodyRect; }
private:
	sf::RectangleShape m_TestBodyRect;
};