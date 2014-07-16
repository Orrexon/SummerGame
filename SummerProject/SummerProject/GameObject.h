//GameObject.h

#pragma once
#include "SFML\Graphics.hpp"

class Collider;
class BoxCollider;
class CircleCollider;

enum eTypes
{
	PLATFORM,
	PLAYER,
	BEGGAR,
	SALESMAN
};
enum BulletId
{
	ENEMY_BULLET,
	PLAYER_BULLET,
	BULLET_ID_COUNT
};

class GameObject
{
public:

	virtual void onCollision(GameObject* other) = 0;
	virtual void update(float deltatime) = 0;
	virtual Collider* getCollider() = 0;
	virtual bool isDead() = 0;
	virtual eTypes getEType() = 0;
protected:
	sf::Vector2f m_position;
	bool m_dead;
	BulletId m_id;
	eTypes m_eType;
	//Collider* m_collider;
	/*BoxCollider* m_boxCollider;
	CircleCollider* m_circleCollider;*/
};