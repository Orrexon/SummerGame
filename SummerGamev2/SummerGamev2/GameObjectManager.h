//GameObjectManager.h
#pragma once
#include <vector>
#include "GameObject.h"

class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager(){}

	void update(float p_delta, sf::Vector2f center);

	void attach(GameObject* obj);
	void initTestBodies();
	void initAnimations();
	void updateAnimatedSprites(float);
	void removeObjects();
	void draw(sf::RenderWindow& window);
	GameObject* getGameObject(int i);
	int getGameObjVecSize();
private:
	std::vector<GameObject*> m_aGameObjects;
};