//CollisionManager.h

#pragma once
#include "stdafx.h"
//#include <vector>
//#include "Collider.h"
//#include "BoxCollider.h"

class CollisionManager
{
public:

	CollisionManager();
	~CollisionManager();

	void Attach(Collider* collider);
	void Update(sf::Vector2f center);
	void RemoveColliders();

	void adjacencyCheck();

	int getCount(){ return count; }
	void sortAdjColliders();
	void attachVecVec(std::vector<Collider*>);
	void collectThemParents();
	void createTheNewColliders();
private:
	int count;
	std::vector<Collider*> m_aColliders;
	std::vector<std::vector<Collider*>> colliderVecVec;
};