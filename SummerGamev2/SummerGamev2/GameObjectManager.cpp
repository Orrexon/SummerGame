//GameObjectManager.cpp
#include "stdafx.h"
//#include "GameObjectManager.h"
//#include "PlatformObject.h"
//#include "Bullet.h"
//#include "SalesMan.h"
GameObjectManager::GameObjectManager(){}

void GameObjectManager::update(float p_delta, sf::Vector2f center)
{
	/*for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		m_aGameObjects[i]->preUpdate(center);
	}*/
	for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		if (m_aGameObjects[i] != nullptr /*&& m_aGameObjects[i]->Update()*/)
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
	SalesMan* test2;
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
		test2 = dynamic_cast<SalesMan*>(m_aGameObjects[i]);
		if (test2)
		{
			test2->initTestBody();
		}
	}
}

void GameObjectManager::initAnimations()
{
	for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		if (dynamic_cast<SalesMan*>(m_aGameObjects[i]))
		{
			dynamic_cast<SalesMan*>(m_aGameObjects[i])->initAnimation();
		}
	}
}

void GameObjectManager::updateAnimatedSprites(float dt)
{
	for (size_t i = 0; i < m_aGameObjects.size(); i++)
	{
		if (dynamic_cast<SalesMan*>(m_aGameObjects[i]))
		{
			dynamic_cast<SalesMan*>(m_aGameObjects[i])->getSprite()->update(sf::seconds(dt));
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
		if (m_aGameObjects[i] /*&& m_aGameObjects[i]->Update()*/)
		{
			if (dynamic_cast<Bullet*>(m_aGameObjects[i]))
			{
				window.draw(dynamic_cast<Bullet*>(m_aGameObjects[i])->getCircle());
			}
			if (dynamic_cast<PlatformObject*>(m_aGameObjects[i]))
			{
				window.draw(dynamic_cast<PlatformObject*>(m_aGameObjects[i])->getSprite());
			}
			if (dynamic_cast<SalesMan*>(m_aGameObjects[i]))
			{
				//window.draw(dynamic_cast<SalesMan*>(m_aGameObjects[i])->getRect());
				window.draw(*dynamic_cast<SalesMan*>(m_aGameObjects[i])->getSprite());
			}
		}
	}
}

GameObject* GameObjectManager::getGameObject(int i)
{
	return m_aGameObjects[i];
}

int GameObjectManager::getGameObjVecSize()
{
	return m_aGameObjects.size();
}