//CollisionManager.cpp
#include "stdafx.h"
//#include "CollisionManager.h"

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


void CollisionManager::Update(sf::Vector2f center)
{
	sf::Vector2f offset;
	count = 0;
	for (size_t i = 0; i < m_aColliders.size() - 1; i++)
	{
		for (size_t j = i + 1; j < m_aColliders.size(); j++)
		{
			if (m_aColliders[i] != nullptr && m_aColliders[j] != nullptr)
			{
				if (m_aColliders[i]->willUpdate(center) && m_aColliders[j]->willUpdate(center))
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
}

void CollisionManager::RemoveColliders()
{
	BoxCollider* temp;
	for (size_t i = 0; i < m_aColliders.size(); i++)
	{
		temp = dynamic_cast<BoxCollider*>(m_aColliders[i]);
		if (m_aColliders[i]->getParent()->isDead()) 
		{
			delete m_aColliders[i];
			m_aColliders[i] = nullptr;
			m_aColliders.erase(m_aColliders.begin() + i);
		}
		if (temp)
		{
			if (temp->getMergeKill())
			{
				delete m_aColliders[i];
				m_aColliders[i] = nullptr;
				m_aColliders.erase(m_aColliders.begin() + i);

			}
		}
	}
}

void CollisionManager::adjacencyCheck()
{
	//go trough the height of the map, one platform collider hight at a time
	for (size_t y = 0; y < 1000; y += 65)
	{
		for (size_t i = 0; i < m_aColliders.size() - 1; i++)
		{
			if (m_aColliders[i]->getParent()->getEType() == PLATFORM)
			{
				if (static_cast<BoxCollider*>(m_aColliders[i])->getPosition().y == y)
				{
					for (size_t j = i + 1; j < m_aColliders.size(); j++)
					{
						if (m_aColliders[j]->getParent()->getEType() == PLATFORM)
						{
							if (static_cast<BoxCollider*>(m_aColliders[i]) &&
								static_cast<BoxCollider*>(m_aColliders[j]))
								//&& not adjacent
							{
								if (static_cast<BoxCollider*>(m_aColliders[j])->getPosition().x -
									static_cast<BoxCollider*>(m_aColliders[j])->GetExtention().x ==
									static_cast<BoxCollider*>(m_aColliders[i])->getPosition().x
									)
								{
									static_cast<BoxCollider*>(m_aColliders[j])->setAdRight(true);
									static_cast<BoxCollider*>(m_aColliders[j])->setMergeKill(true);
								}
								if (static_cast<BoxCollider*>(m_aColliders[i])->getPosition().x +
									static_cast<BoxCollider*>(m_aColliders[i])->GetExtention().x ==
									static_cast<BoxCollider*>(m_aColliders[j])->getPosition().x)
								{
									static_cast<BoxCollider*>(m_aColliders[i])->setAdLeft(true);
									static_cast<BoxCollider*>(m_aColliders[i])->setMergeKill(true);
								}
							}
						}
					}
				}
			}
		}
	}
}
void CollisionManager::sortAdjColliders()
{
	//for every row, push the adjecant colliders in the 2d vector
	for (size_t y = 0; y <= 1000; y += 65)
	{
		std::vector<Collider*> temp;
		for (size_t i = 0; i < m_aColliders.size(); i++)
		{
			if (dynamic_cast<BoxCollider*>(m_aColliders[i]) &&
				dynamic_cast<BoxCollider*>(m_aColliders[i])->getPosition().y == y)
			{
				if (dynamic_cast<BoxCollider*>(m_aColliders[i])->getAdLeft() ||
					dynamic_cast<BoxCollider*>(m_aColliders[i])->getAdRight())
				{

					temp.push_back(dynamic_cast<BoxCollider*>(m_aColliders[i]));
				}
				if (dynamic_cast<BoxCollider*>(m_aColliders[i])->getAdRight() &&
					!dynamic_cast<BoxCollider*>(m_aColliders[i])->getAdLeft())
				{
					temp.push_back(dynamic_cast<BoxCollider*>(m_aColliders[i]));
				}
			}
		}
		if (temp.size() > 0)
		{
			attachVecVec(temp);
			temp.clear();
		}
	}
}
void CollisionManager::attachVecVec(std::vector<Collider*> vec)
{
	colliderVecVec.push_back(vec);
}

void CollisionManager::collectThemParents()
{
	for (size_t i = 0; i < colliderVecVec.size(); i++)
	{
		for (size_t j = 0; j < colliderVecVec[i].size(); j++)
		{
			static_cast<BoxCollider*>(colliderVecVec[i][j])->pushParent(
				static_cast<BoxCollider*>(colliderVecVec[i][j])->getParent());
		}
	}
}
void CollisionManager::createTheNewColliders()
{
	adjacencyCheck();
	sortAdjColliders();
	collectThemParents();
	for (size_t i = 0; i < colliderVecVec.size(); i++)
	{
		//how many colliders adjacent in each row
		int size = colliderVecVec[i].size();
	}

}