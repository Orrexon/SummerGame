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
	m_offset = { 0.f, 0.f };
	BoxCollider* temp = dynamic_cast<BoxCollider*>(other);
	float A = m_extention.x / 2.f;
	float B = temp->m_extention.x / 2.f;
	float C = (m_position.x ) - (temp->m_position.x );
	
	float X = m_extention.y / 2.f;
	float Y = temp->m_extention.y / 2.f;
	float Z = (m_position.y) - (temp->m_position.y);
	
	float deltaX = (std::fabs(C) - (A + B));
	float deltaY = (std::fabs(Z) - (X + Y));
	
	if (std::fabs(C) <= (A + B))
	{
		if (std::fabs(Z) <= (X + Y))
		{
			if (deltaX >= deltaY)
			{
				if (m_position.x >= temp->m_position.x)
				{
					deltaX = -deltaX;
				}
				m_offset.x = deltaX;
			}
			else
			{
				if (m_position.y >= temp->m_position.y)
				{
					deltaY = -deltaY;
				}
				m_offset.y = deltaY;
			}
			return true;
		}
	}
	return false;
}

void BoxCollider::onCollision(Collider* other)
{
	BoxCollider* temp = dynamic_cast<BoxCollider*>(other);
	std::cout << "BoxCollider::onCollision()" << std::endl;
	m_parent->onCollision(temp->m_parent);
}