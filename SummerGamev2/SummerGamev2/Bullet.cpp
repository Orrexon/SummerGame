//Bullet.cpp
#include "stdafx.h"
//#include "Bullet.h"
//#include "CircleCollider.h"
//#include <iostream>

Bullet::Bullet(Collider* collider, sf::Vector2f pos)
{
	m_circleCollider = dynamic_cast<CircleCollider*> (collider);
	if (m_circleCollider != nullptr)
	{
		m_circleCollider->setParent(this);
	}
	m_position = pos;
	m_dead = false;
	m_update = true;
	m_eType = BULLET;
}

Bullet::~Bullet()
{
	if (m_circleCollider != nullptr)
	{
		delete m_circleCollider;
		m_circleCollider = nullptr;
	}
	m_TestCircle.setFillColor(sf::Color::Cyan);
}

void Bullet::onCollision(GameObject* other)
{
	{
		Bullet* temp = dynamic_cast<Bullet*> (other);
		if (temp)
		{
			m_dead = true;
		}
	}
	{
		SalesMan* temp = dynamic_cast<SalesMan*> (other);
		if (temp)
		{
			m_dead = true;
		}
	}
	{
		PlatformObject* temp = dynamic_cast<PlatformObject*> (other);
		if (temp)
		{
			m_dead = true;
		}
	}
}
void Bullet::preUpdate(sf::Vector2f center)
{

}
void Bullet::update(float deltatime)
{
	m_position += m_velocity;
	if (m_circleCollider != nullptr)
	{
		m_circleCollider->setPosition(m_position);
	}
	m_TestCircle.setPosition(m_position);
}

void Bullet::InitTestBody()
{
	m_TestCircle.setPosition(m_position);
	m_TestCircle.setFillColor(sf::Color::Red);
	m_TestCircle.setRadius(m_circleCollider->getRadius());
	m_TestCircle.setOrigin(m_circleCollider->getRadius(), m_circleCollider->getRadius());

}