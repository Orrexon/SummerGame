//PlatformObject.cpp

#include "PlatformObject.h"

PlatformObject::PlatformObject(Collider* collider, sf::Vector2f position)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_dead = false;
	m_eType = PLATFORM;
}
PlatformObject::PlatformObject(Collider* collider, sf::Vector2f position, sf::Sprite sprite)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_sprite = sprite;
	m_dead = false;
	m_eType = PLATFORM;
	m_sprite.setOrigin(m_boxCollider->GetExtention() / 2.f);
	m_sprite.setPosition(position);
}
void PlatformObject::initTestBody()
{
	m_TestBodyRect.setSize(m_boxCollider->GetExtention());
	m_TestBodyRect.setFillColor(sf::Color::Yellow);
	m_TestBodyRect.setPosition(m_position);
	m_TestBodyRect.setOrigin(m_TestBodyRect.getSize() / 2.f);
	
}

void PlatformObject::update(float deltatime)
{
	/*m_boxCollider->SetPosition(m_position);
	m_TestBodyRect.setPosition(m_position);*/
}
void PlatformObject::onCollision(GameObject* other)
{
	//printf("GROUNDNDNDNDNDNDNDNDNDNDNDNDNDNDND");
}

eTypes PlatformObject::getEType()
{
	return m_eType;
}