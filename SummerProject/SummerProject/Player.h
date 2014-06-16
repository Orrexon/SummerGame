//Player.h

#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(Collider* collider, sf::Vector2f position);
	

	void update(float deltatime);

	void initTestbody();

	void onCollision(GameObject* other);


	sf::RectangleShape& GetRect() { return TestBodyRect; }
private:
	bool onGround;
	sf::Vector2f m_velocity;
	sf::CircleShape TestBodyCircle;
	sf::RectangleShape TestBodyRect;
};