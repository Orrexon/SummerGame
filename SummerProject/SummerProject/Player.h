//Player.h

#pragma once
#include "GameObject.h"
#include "PlatformObject.h"
#include "InputManager.h"
class Player : public GameObject
{
public:
	Player(Collider* collider, sf::Vector2f position, InputManager* input);
	

	void update(float deltatime);

	void initTestbody();

	void onCollision(GameObject* other);

	//BoxCollider* getBoxCollider() { return m_boxCollider; }
	Collider* getCollider() { return m_boxCollider; }
	sf::RectangleShape& GetRect() { return TestBodyRect; }
	bool isDead() { return m_dead; }
private:
	InputManager* m_inputMgr;
	bool onGround;
	sf::Vector2f m_velocity;
	BoxCollider* m_boxCollider;
	sf::CircleShape TestBodyCircle;
	sf::RectangleShape TestBodyRect;
};