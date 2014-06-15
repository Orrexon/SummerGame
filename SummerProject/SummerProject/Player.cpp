//PLayer.cpp

#include "GameObject.h"
#include "Player.h"
Player::Player(Collider* collider, sf::Vector2f position)
{
	m_collider = collider;
	m_position = position;
}

void Player::initTestbody()
{
	TestBodyRect.setFillColor(sf::Color::Blue);
	TestBodyRect.setPosition(m_position);
//	TestBodyRect.setOrigin(m_collider->m_extention )
}