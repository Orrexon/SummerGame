//Bullet.h

#pragma once
//#include "stdafx.h"
//#include "GameObject.h"
//#include "CircleCollider.h"
//#include "SalesMan.h"
//#include "PlatformObject.h"

class Bullet : public GameObject
{
public:
	Bullet(Collider* collider, sf::Vector2f pos);
	~Bullet();

	virtual void onCollision(GameObject* other);
	virtual void preUpdate(sf::Vector2f center);
	virtual void update(float deltatime);
	virtual bool Update(){ return m_update; }
	Collider* getCollider()  { return m_circleCollider; }   
	virtual eTypes getEType(){ return m_eType; }
	void setVelocity(sf::Vector2f vel) { m_velocity = vel; }

	void InitTestBody();

	sf::CircleShape getCircle() {return m_TestCircle; }

	bool isDead() { return m_dead; }

	void setId(BulletId i){ m_id = i; }
	int getId(){ return m_id; }

private:
	sf::Vector2f m_velocity;
	CircleCollider* m_circleCollider;
	sf::CircleShape m_TestCircle;
};