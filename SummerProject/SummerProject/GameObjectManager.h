//GameObjectManager.h
#pragma once
#include <vector>
#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager(){}

	void update(float p_delta);

	void attach(GameObject* obj);
	void initTestBodies();
	void removeObjects();
	void draw(sf::RenderWindow& window);
	GameObject* getGameObject(int i);
	int getGameObjVecSize();
private:
	std::vector<GameObject*> m_aGameObjects;
};