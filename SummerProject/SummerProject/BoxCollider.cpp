//BoxCollider.cpp
#include <iostream>
#include "BoxCollider.h"
#include "CircleCollider.h"

BoxCollider::BoxCollider(sf::Vector2f pos, sf::Vector2f ext)
{
	m_position = pos;
	m_extention = ext;
}


bool BoxCollider::overlap(Collider* other, sf::Vector2f& offset)
{
	MathNerd mathNerd;
	m_offset = { 0.f, 0.f };
	{
		BoxCollider* temp = dynamic_cast<BoxCollider*>(other);
		if (temp != nullptr)
		{
			float A = m_extention.x / 2.f;
			float B = temp->m_extention.x / 2.f;
			float C = (m_position.x) - (temp->m_position.x);

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
		}
	}
	{
		CircleCollider* temp = dynamic_cast<CircleCollider*> (other);
		if (temp)
		{
			float W = m_extention.x*0.5f;
			float H = m_extention.y*0.5f;
			float R = temp->getRadius();

			//The corner points
			sf::Vector2f topright = sf::Vector2f(m_position.x + W, m_position.y - H);
			sf::Vector2f botright = sf::Vector2f(m_position.x + W, m_position.y + H);
			sf::Vector2f topleft = sf::Vector2f(m_position.x - W, m_position.y - H);
			sf::Vector2f botleft = sf::Vector2f(m_position.x - W, m_position.y + H);

			//The closest points on the sides
			sf::Vector2f ClosestPointRight = mathNerd.ClosestPointOnLine(topright, botright, temp->getPosition());
			sf::Vector2f ClosestPointBottom = mathNerd.ClosestPointOnLine(botright, botleft, temp->getPosition());
			sf::Vector2f ClosestPointLeft = mathNerd.ClosestPointOnLine(botleft, topleft, temp->getPosition());
			sf::Vector2f ClosestPointTop = mathNerd.ClosestPointOnLine(topleft, topright, temp->getPosition());


			//Bulky deltas and their vectors
			float deltax = ClosestPointRight.x - temp->getPosition().x;
			float deltay = ClosestPointRight.y - temp->getPosition().y;
			float deltaxB = ClosestPointBottom.x - temp->getPosition().x;
			float deltayB = ClosestPointBottom.y - temp->getPosition().y;
			float deltaxL = ClosestPointLeft.x - temp->getPosition().x;
			float deltayL = ClosestPointLeft.y - temp->getPosition().y;
			float deltaxT = ClosestPointTop.x - temp->getPosition().x;
			float deltayT = ClosestPointTop.y - temp->getPosition().y;
			sf::Vector2f distanceright(fabs(deltax), fabs(deltay));
			sf::Vector2f distancerbottom(fabs(deltaxB), fabs(deltayB));
			sf::Vector2f distancerLeft(fabs(deltaxL), fabs(deltayL));
			sf::Vector2f distancerTop(fabs(deltaxT), fabs(deltayT));

			//Checking to see if the distance between each "closest points"
			// and the circle's center is less than the circle's radius.
			if (distanceright.x < R && distanceright.y < R)	{ return true; }
			if (distancerbottom.x < R && distancerbottom.y < R)	{ return true; }
			if (distancerLeft.x < R && distancerLeft.y < R)		{ return true; }
			if (distancerTop.x < R && distancerTop.y < R)		{ return true; }

			//Is the circle within the rectangle?
			if (temp->getPosition().x < topright.x && temp->getPosition().y > topright.y
				&& temp->getPosition().x < botright.x && temp->getPosition().y < botright.y
				&& temp->getPosition().x > topleft.x && temp->getPosition().y > topleft.y
				&& temp->getPosition().x > botleft.x && temp->getPosition().y < botleft.y)	{
				return true;
			}
		}
	}
	return false;
}

void BoxCollider::onCollision(Collider* other)
{
	m_parent->onCollision(other->getParent());
	/*{
		BoxCollider* temp = dynamic_cast<BoxCollider*>(other);
		if (temp)
		{
			std::cout << "BoxCollider::onCollision()" << std::endl;
			m_parent->onCollision(temp->m_parent);
		}
	}
	{
		CircleCollider* temp = dynamic_cast<CircleCollider*>(other);
		if (temp)
		{
			std::cout << "Bullet vs Box! \n" << std::endl;
			m_parent->onCollision(temp->getParent());
		}
	}*/
}