//CollisionManager.h

#pragma once
#include <vector>
#include "Collider.h"
#include "BoxCollider.h"

class CollisionManager
{
public:

	CollisionManager();
	~CollisionManager();

	void Attach(Collider* collider);
	void setUpCollisionPairs(std::vector<Collider*>& colliders);
	void Update();
	void RemoveColliders();

	void adjacencyCheck();

	int getCount(){ return count; }
private:
	int count;
	std::vector<Collider*> m_aColliders;
	std::vector<std::pair<int, int>> m_aCollisionPairs;
};