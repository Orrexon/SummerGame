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

private:
	std::vector<Collider*> m_aColliders;
};