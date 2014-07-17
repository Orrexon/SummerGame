//CollisionManager.cpp

#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}
CollisionManager::~CollisionManager()
{
	for (auto it = m_aColliders.begin(); it != m_aColliders.end(); it++)
	{
		if (*it != nullptr)
		{
			delete *it;
			*it = nullptr;
		}
	}
	m_aColliders.clear();
}

void CollisionManager::Attach(Collider* collider)
{
	m_aColliders.push_back(collider);
}


void CollisionManager::Update()
{
	sf::Vector2f offset;
	count = 0;
	for (size_t i = 0; i < m_aColliders.size() - 1; i++)
	{
		for (size_t j = i + 1; j < m_aColliders.size(); j++)
		{
			if (m_aColliders[i] != nullptr && m_aColliders[j] != nullptr)
			{

					//if both colliders are platforms, don't check for overlap
					if (m_aColliders[i]->getParent()->getEType() == PLATFORM && m_aColliders[j]->getParent()->getEType() == PLATFORM) continue;

					if (m_aColliders[i]->overlap(m_aColliders[j], offset))
					{
						m_aColliders[i]->onCollision(m_aColliders[j]);
						m_aColliders[j]->onCollision(m_aColliders[i]);
						count++;
					}


				
			}
		}
	}
}

void CollisionManager::RemoveColliders()
{
	for (size_t i = 0; i < m_aColliders.size(); i++)
	{
		if (m_aColliders[i]->getParent()->isDead())
		{
			delete m_aColliders[i];
			m_aColliders[i] = nullptr;
			m_aColliders.erase(m_aColliders.begin() + i);
		}

	}
}

void CollisionManager::adjacencyCheck()
{

	////////////////////////////////////////////////////
	// TOO COMPLICATED FOR NOW
	///////////////////////////////////////////////////
	std::vector<Collider*> temp;


	int count = 0;
	std::vector<float> x;
	//go trough the height of the map, one platform collider hight at a time
	for (size_t y = 0; y < 1000; y += 65)
	{
		for (size_t i = 0; i < m_aColliders.size(); i++)
		{
			if (dynamic_cast<BoxCollider*>(m_aColliders[i]))
			if (dynamic_cast<BoxCollider*>(m_aColliders[i])->getPosition().y == y)
			{
				x.push_back(dynamic_cast<BoxCollider*>(temp[i])->getPosition().x);
				temp.push_back(m_aColliders[i]);
			}
		}
		if (temp.size() == 0)
		{
			continue;
		}
		int adjacentcount = 0;
		for (size_t i = 0; i < temp.size() - 1; i++)
		{
			for (size_t j = i + 1; j < temp.size(); j++)
			{
				if (dynamic_cast<BoxCollider*>(temp[i]) && dynamic_cast<BoxCollider*>(temp[j]))
				{
					if (dynamic_cast<BoxCollider*>(temp[i])->getPosition().x -
						dynamic_cast<BoxCollider*>(temp[i])->GetExtention().x ==
						dynamic_cast<BoxCollider*>(temp[j])->getPosition().x
						||
						dynamic_cast<BoxCollider*>(temp[i])->getPosition().x +
						dynamic_cast<BoxCollider*>(temp[i])->GetExtention().x ==
						dynamic_cast<BoxCollider*>(temp[j])->getPosition().x)
					{
						++adjacentcount;
					}
				}
			}
		}
		if (count > 0)
		{
			//get the middle x value
			float midX = 0;
			for (size_t i = 0; i < x.size(); i++)
			{
				midX += x[i];
			}
			midX /= count;
			BoxCollider* p = new BoxCollider(sf::Vector2f(midX, y), sf::Vector2f(count*65.f, 65.f));
			//push new collider into original vector
			m_aColliders.push_back(p);
			count = 0;
		}
	}
}