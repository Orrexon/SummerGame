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
	for (size_t i = 0; i < m_aColliders.size() - 1; i++)
	{
		for (size_t j = i + 1; j < m_aColliders.size(); j++)
		{
			if (m_aColliders[i] != nullptr && m_aColliders[j] != nullptr)
			{
				if (m_aColliders[i]->overlap(m_aColliders[j], offset))
				{
					m_aColliders[i]->onCollision(m_aColliders[j]);
					m_aColliders[j]->onCollision(m_aColliders[i]);
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