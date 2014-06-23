//GameObjectManager.cpp
#include "GameObjectManager.h"
#include "PlatformObject.h"
#include "Bullet.h"
GameObjectManager::GameObjectManager(){}

void GameObjectManager::update(float p_delta)
{
	for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		if (m_aGameObjects[i] != nullptr)
		{
			m_aGameObjects[i]->update(p_delta);
		}
	}
}

void GameObjectManager::attach(GameObject* obj)
{
	m_aGameObjects.push_back(obj);
}

void GameObjectManager::initTestBodies()
{
	PlatformObject* test;
	Bullet* test1;
	for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		test = dynamic_cast<PlatformObject*>(m_aGameObjects[i]);
		if (test != nullptr)
		{
			test->initTestBody();
		}
		test1 = dynamic_cast<Bullet*>(m_aGameObjects[i]);
		if (test1 != nullptr)
		{
			test1->InitTestBody();
		}
	}
}

void GameObjectManager::removeObjects()
{
	for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		if (m_aGameObjects[i]->isDead())
		{
			delete m_aGameObjects[i];
			m_aGameObjects[i] = nullptr;
			m_aGameObjects.erase(m_aGameObjects.begin() + i);
		}
	}
}

void GameObjectManager::draw(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		if (m_aGameObjects[i])
		{
			if (dynamic_cast<Bullet*>(m_aGameObjects[i]))
			{
				window.draw(dynamic_cast<Bullet*>(m_aGameObjects[i])->getCircle());
			}
		}
	}
}