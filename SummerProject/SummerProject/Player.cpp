//PLayer.cpp

#include "GameObject.h"
#include "Player.h"
#include "BoxCollider.h"
Player::Player(Collider* collider, sf::Vector2f position)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_position = position;
}

void Player::initTestbody()
{
	TestBodyRect.setSize(m_boxCollider->GetExtention());
	TestBodyRect.setFillColor(sf::Color::Blue);
	TestBodyRect.setPosition(m_position);
	TestBodyRect.setOrigin(m_boxCollider->GetExtention() / 2.f);
}

void Player::update(float deltatime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		TestBodyRect.move(0.1f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		TestBodyRect.move(-0.1f, 0.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		TestBodyRect.move(0.0f, -1.0f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		TestBodyRect.move(0.0f, 1.0f);
	}
}

void Player::onCollision(GameObject* other)
{
	printf("don't be good niggah, be great");
}