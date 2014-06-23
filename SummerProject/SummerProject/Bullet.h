//Bullet.h

#pragma once
#include "GameObject.h"
#include "CircleCollider.h"

class Bullet : public GameObject
{
public:
	Bullet(Collider* collider, sf::Vector2f pos);
	~Bullet();

	virtual void onCollision(GameObject* other);
	virtual void update(float deltatime);
	Collider* getCollider()  { return m_circleCollider; }   

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