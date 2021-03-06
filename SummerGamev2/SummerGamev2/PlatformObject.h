//PlatformObject.h

#pragma once
//#include <SFML\Graphics.hpp>
//#include "GameObject.h"
//#include "BoxCollider.h"

class PlatformObject : public GameObject
{
public:
	PlatformObject(Collider* collider, sf::Vector2f position);
	PlatformObject(Collider* collider, sf::Vector2f position, sf::Sprite sprite);
	void initTestBody();
	virtual void onCollision(GameObject* other);
	virtual void preUpdate(sf::Vector2f center);
	virtual void update(float deltatime);
	virtual bool Update(){ return m_update; }
	virtual eTypes getEType();
	//virtual BoxCollider* getBoxCollider() { return m_boxCollider; }
	Collider* getCollider() { return m_boxCollider; }

	sf::RectangleShape GetRect() { return m_TestBodyRect; }
	sf::Vector2f getPosition() { return m_position; }
	sf::Sprite getSprite(){ return m_sprite; }
	bool isDead() { return m_dead; }
private:
	sf::RectangleShape m_TestBodyRect;
	sf::Sprite m_sprite;
	BoxCollider* m_boxCollider;
};