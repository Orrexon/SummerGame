//Player.h

#pragma once
#include "GameObject.h"
class Player : public GameObject
{
public:
	Player(Collider* collider, sf::Vector2f position);
	

	void update(float deltatime);

	void initTestbody();

private:
	sf::CircleShape TestBodyCircle;
	sf::RectangleShape TestBodyRect;
};