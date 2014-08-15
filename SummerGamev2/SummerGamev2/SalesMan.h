//SalesMan.h
#pragma once
#include "stdafx.h"
//#include "GameObject.h"
//#include "Bullet.h"
//#include "BoxCollider.h"

class SalesMan : public GameObject
{
public:
	SalesMan(Collider* collider, sf::Vector2f position);
	~SalesMan(){}

	virtual void onCollision(GameObject* other);
	virtual void preUpdate(sf::Vector2f center);
	virtual void update(float deltatime);
	virtual bool Update(){ return m_update; }
	virtual Collider* getCollider(){ return m_boxCollider; }
	virtual bool isDead() { return m_dead; }
	virtual eTypes getEType() { return m_eType; }
	void initTestBody();
	sf::RectangleShape getRect() { return m_testBodyRect; }

	void initAnimation();
	void insertAnimation(std::string name, Animation* anim);
	Animation* getAnimation(std::string);
	AnimatedSprite* getSprite() { return m_sprite; }
private:
	BoxCollider* m_boxCollider;
	sf::RectangleShape m_testBodyRect;
	std::map <std::string, Animation*> m_animations;
	AnimatedSprite* m_sprite;
};