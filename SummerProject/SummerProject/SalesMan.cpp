//SalesMan.cpp

#include "SalesMan.h"

SalesMan::SalesMan(Collider* collider, sf::Vector2f position)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_dead = false;
}
void SalesMan::onCollision(GameObject* other)
{
	{
		Bullet* temp = dynamic_cast<Bullet*> (other);
		if (temp)
		{
			if (temp->getId() == PLAYER_BULLET)
			{
				m_dead = true;
			}
		}
	}
	printf("salesman colliding!\n");
}
void SalesMan::update(float deltatime)
{
	m_boxCollider->SetPosition(m_position);
	m_testBodyRect.setPosition(m_position);
}

void SalesMan::initTestBody()
{
	m_testBodyRect.setSize(m_boxCollider->GetExtention());
	m_testBodyRect.setOrigin(m_testBodyRect.getSize() / 2.f);
	m_testBodyRect.setFillColor(sf::Color::Green);
	m_testBodyRect.setPosition(m_position);
}