//SalesMan.h
#pragma once
#include "GameObject.h"
#include "Bullet.h"

class SalesMan : public GameObject
{
public:
	SalesMan();
	~SalesMan();

	virtual void onCollision(GameObject* other);
	virtual void update(float deltatime);
	virtual Collider* getCollider();
	virtual bool isDead();
};