//PLayer.cpp

#include "GameObject.h"
#include "Player.h"
#include "BoxCollider.h"
#include "PlatformObject.h"
Player::Player(Collider* collider, sf::Vector2f position)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_type = "Player";
	m_velocity = { 0.f, 0.f };
	onGround = false;
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
	m_velocity = { 0.0f, 0.0f };
	sf::Vector2f gravity = { 0.f, 0.05f };
	sf::Vector2f jumpvel = { 0.f, -0.3f };
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity = { 0.1f, 0.0f };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity = { -0.1f, 0.0f };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity = { 0.0f, -0.1f };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity = { 0.0f, 0.1f };
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_velocity += jumpvel;
		onGround = false;
	}
	if (!onGround)
	{
		m_velocity += gravity;
	}
	
	m_position += m_velocity;
	m_boxCollider->SetPosition(m_position);
	TestBodyRect.setPosition(m_position);
}

void Player::onCollision(GameObject* other)
{
	
	if (dynamic_cast<PlatformObject*>(other) != nullptr)
	{
		onGround = true;
	}
	m_position += m_boxCollider->getOffset();
	//printf("don't be good niggah, be great");
}