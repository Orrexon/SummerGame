//PLayer.cpp

#include "GameObject.h"
#include "Player.h"
#include "BoxCollider.h"


Player::Player(Collider* collider, sf::Vector2f position, InputManager* input)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_inputMgr = input;
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
	const sf::Vector2f gravity = { 0.f, 9.8f };
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		m_velocity.x = deltatime*200.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		m_velocity.x = deltatime*-200.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		m_velocity.y = deltatime*-200.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_velocity.y = deltatime*200.f;
	}
	if (m_inputMgr->IsDownOnce(sf::Keyboard::Space) && onGround)
	{
		m_velocity.y = -gravity.y;
		onGround = false;
	}
	if (!onGround)
	{
		m_velocity.y += deltatime * gravity.y;
	}
	m_position += m_velocity;
	m_boxCollider->SetPosition(m_position);
	TestBodyRect.setPosition(m_position);
	m_velocity *= 0.9f;
	onGround = false;
}

void Player::onCollision(GameObject* other)
{
	PlatformObject* platform = dynamic_cast<PlatformObject*>(other);
	if (platform != nullptr)
	{
		if (m_position.y  <= platform->getPosition().y )
		{
  			onGround = true;
		}
		m_position += m_boxCollider->getOffset();
	}
	
	//m_velocity *= 0.9f;
	//printf("Player::onCollision()\n")
}