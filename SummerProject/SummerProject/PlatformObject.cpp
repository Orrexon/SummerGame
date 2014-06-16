//PlatformObject.cpp

#include "PlatformObject.h"

PlatformObject::PlatformObject(Collider* collider, sf::Vector2f position)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_type = "PlatformObject";
}
void PlatformObject::initTestBody()
{
	m_TestBodyRect.setFillColor(sf::Color::Yellow);
	m_TestBodyRect.setSize(m_boxCollider->GetExtention());
	m_TestBodyRect.setOrigin(m_boxCollider->GetExtention() / 2.f);
	m_TestBodyRect.setPosition(m_position);
}
void PlatformObject::onCollision(GameObject* other)
{
	printf("GROUNDNDNDNDNDNDNDNDNDNDNDNDNDNDND");
}