//SalesMan.cpp
#include "stdafx.h"
//#include "SalesMan.h"

SalesMan::SalesMan(Collider* collider, sf::Vector2f position)
:m_sprite(nullptr)
{
	m_boxCollider = dynamic_cast<BoxCollider*>(collider);
	m_boxCollider->setParent(this);
	m_position = position;
	m_dead = false;
	m_update = true;
	m_eType = SALESMAN;
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
	m_position += other->getCollider()->getOffset();
	printf("salesman colliding!\n");
}
void SalesMan::preUpdate(sf::Vector2f center)
{
	sf::Vector2f vDist = center - m_position;
	float length = (vDist.x*vDist.x + vDist.y*vDist.y);
	if (length < 1100.f*1100.f){ m_update = true; }
	else { m_update = false; }
}
void SalesMan::update(float deltatime)
{
	m_sprite->play();
	m_boxCollider->SetPosition(m_position);
	m_testBodyRect.setPosition(m_position);
	m_sprite->setPosition(m_position);
	m_sprite->setOrigin(static_cast<BoxCollider*>(getCollider())->GetExtention() / 2.f);
}

void SalesMan::initTestBody()
{
	m_testBodyRect.setSize(m_boxCollider->GetExtention());
	m_testBodyRect.setOrigin(m_testBodyRect.getSize() / 2.f);
	m_testBodyRect.setFillColor(sf::Color::Green);
	m_testBodyRect.setPosition(m_position);
}

void SalesMan::initAnimation()
{
	sf::Texture* SpriteSheet = new sf::Texture();
	if (!SpriteSheet->loadFromFile("../data/sprites/salesman.png"))
	{
		printf("salesman::initAnimation something's wrong\n");
	}
	Animation* anim_idle = new Animation;
	anim_idle->setSpriteSheet(*SpriteSheet);
	anim_idle->addFrame(sf::IntRect(78, 0, 60, 110));
	anim_idle->addFrame(sf::IntRect(78+1*60, 0, 60, 110));
	anim_idle->addFrame(sf::IntRect(78 + 2 * 60, 0, 60, 110));
	anim_idle->addFrame(sf::IntRect(78 + 3 * 60, 0, 60, 110));
	anim_idle->addFrame(sf::IntRect(78 + 4 * 60, 0, 60, 110));
	anim_idle->addFrame(sf::IntRect(78 + 5 * 60, 0, 60, 110));
	insertAnimation("idle", anim_idle);
	m_sprite = new AnimatedSprite(sf::seconds(0.2), true, true);
	m_sprite->setAnimation(*getAnimation("idle"));
}

void SalesMan::insertAnimation(std::string name, Animation* anim)
{
	std::pair<std::string, Animation*> pair(name, anim);
	m_animations.insert(pair);
}

Animation* SalesMan::getAnimation(std::string name)
{
	std::map<std::string, Animation*>::iterator it = m_animations.find(name);
	if (it == m_animations.end())
	{
		std::cout << "No Such animation as: " << name << std::endl;
		return nullptr;
	}
	return it->second;
}