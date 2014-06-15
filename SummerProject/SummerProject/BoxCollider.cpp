//BoxCollider.cpp
#include <iostream>
#include "BoxCollider.h"

BoxCollider::BoxCollider(sf::Vector2f pos, sf::Vector2f ext)
{
	m_position = pos;
	m_extention = ext;
}


bool BoxCollider::overlap(Collider* other, sf::Vector2f& offset)
{
	BoxCollider* temp = dynamic_cast<BoxCollider*>(other);
	float A = m_extention.x / 2.f;
	float B = temp->m_extention.x / 2.f;
	float C = std::fabs(m_position.x - temp->m_position.x);

	float X = m_extention.y / 2.f;
	float Y = temp->m_extention.y / 2.f;
	float Z = std::fabs(m_position.y - temp->m_position.y);

	if (C <= (A + B))
	{
		if (Z <= (X + Y))
		{
			float deltaX = C - (A + B);
			float deltaY = Z - (X + Y);
			if (deltaX > deltaY)
			{
				if (m_position.x >= temp->m_position.x)
				{
					deltaX = -deltaX;
				}
				offset.x = deltaX;
			}
			if (deltaX <= deltaY)
			{
				if (m_position.y <= temp->m_position.y)
				{
					deltaY = -deltaY;
				}
				offset.y = deltaY;
			}
			return true;
		}
	}
	return false;
}

void BoxCollider::onCollision(Collider* other)
{
	std::cout << "BoxCollider::onCollision()" << std::endl;
	//other->parent->onCollision;
}