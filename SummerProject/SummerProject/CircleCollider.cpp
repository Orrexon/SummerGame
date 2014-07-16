//CircleCollider.cpp

#include "CircleCollider.h"
#include "BoxCollider.h"
#include <assert.h>

CircleCollider::CircleCollider(sf::Vector2f pos, float rad)
{
	m_position = pos;
	m_radius = rad;
}

CircleCollider::~CircleCollider(){}

bool CircleCollider::overlap(Collider* other, sf::Vector2f& offset)
{
	{
		CircleCollider* temp = dynamic_cast<CircleCollider*>(other);
		if (temp != nullptr)
		{
			sf::Vector2f distance = m_position - temp->m_position;
			if (powf(distance.x, 2.f) + powf(distance.y, 2.f) <= powf(m_radius + temp->m_radius, 2.f))
			{
				float length = sqrtf(powf(distance.x, 2.f) + powf(distance.y, 2.f));
				distance /= length;
				m_offset = distance * m_radius;
				return true;
			}
		}
	}
	return false;
}
void CircleCollider::onCollision(Collider* other)
{
	m_parent->onCollision(other->getParent());
	/*{
		CircleCollider* temp = dynamic_cast<CircleCollider*> (other);
		if (temp)
		{
			if (!getParent()->isDead())
			{
				m_parent->onCollision(temp->m_parent);
			}
		}
	}
	{
		BoxCollider* temp = dynamic_cast<BoxCollider*>(other);
		if (temp)
		{
			printf("box vs bullet");
			m_parent->onCollision(temp->getParent());
		}
	}*/
}

