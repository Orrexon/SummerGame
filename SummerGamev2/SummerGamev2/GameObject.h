//GameObject.h

#pragma once
#include "stdafx.h"
//#include "SFML\Graphics.hpp"
//
//class Collider;
//class BoxCollider;
//class CircleCollider;

enum eTypes
{
	PLATFORM,
	PLAYER,
	BEGGAR,
	SALESMAN,
	BULLET
};
enum BulletId
{
	ENEMY_BULLET,
	PLAYER_BULLET
};

class GameObject
{
public:

	virtual void onCollision(GameObject* other) = 0;
	virtual void preUpdate(sf::Vector2f center) = 0;
	virtual void update(float deltatime) = 0;
	virtual Collider* getCollider() = 0;
	virtual bool isDead() = 0;
	virtual bool Update() = 0;
	virtual eTypes getEType() = 0;
protected:
	sf::Vector2f m_position;
	bool m_dead, m_update;
	BulletId m_id;
	eTypes m_eType;
};