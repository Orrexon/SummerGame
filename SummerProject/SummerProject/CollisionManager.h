//CollisionManager.h

#pragma once
#include <vector>
#include "Collider.h"

class CollisionManager
{
public:

	CollisionManager();
	~CollisionManager();

	void Attach(Collider* collider);

	void Update();
	void RemoveColliders();

private:
	std::vector<Collider*> m_aColliders;
};