//startstate.cpp
#include "stdafx.h"
//#include <iostream>
//
//#include "StartState.h"




StartState::StartState(Core* p_Core) :NavGraph(false)
{
	m_sCurrentState = "StartState";
	m_core = p_Core;

}




/*	Called upon entering state */
bool StartState::EnterState()
{
	printf("StartState");
	m_core->m_level->load("../data/map/map.txt", m_core->m_spriteMgr);
	//m_core->m_level->load("../data/map/map.txt", m_core->m_spriteMgr);
	///*GraphHelper_CreateGrid(NavGraph, 1000, 1000, 25, 25);
	//Graph_SearchAStar<SparseGraph<NavGraphNode<>, NavGraphEdge>, Heuristic_Euclid> Astar(NavGraph, 143, 22);*/
	//BoxCollider* collider = new BoxCollider(m_core->m_level->getPlayerStartPosition(), sf::Vector2f(50, 64));
	//m_player = new Player(collider, m_core->m_level->getPlayerStartPosition(), m_core->m_inputMgr,
	//	m_core->m_collMgr, m_core->m_GameObjMgr);


	////m_player->initTestbody();

	//m_core->m_collMgr->Attach(m_player->getCollider());

	///*PlatformObject* temp;
	//SparseGraph<NavGraphNode<>, NavGraphEdge>::ConstNodeIterator ConstNodeItr(NavGraph);
	//for (const SparseGraph<NavGraphNode<>, NavGraphEdge>::NodeType* pN = ConstNodeItr.begin();
	//	!ConstNodeItr.end();
	//	pN = ConstNodeItr.next())
	//{
	//	for (int i = 0; i < m_core->m_GameObjMgr->getGameObjVecSize(); ++i)
	//	{
	//		if (temp = dynamic_cast<PlatformObject*>(m_core->m_GameObjMgr->getGameObject(i)))
	//		{
	//			if (pN->getPosition().x <= temp->getPosition().x + temp->GetRect().getSize().x / 2 &&
	//				pN->getPosition().x >= temp->getPosition().x - temp->GetRect().getSize().x / 2 &&
	//				pN->getPosition().y >= temp->getPosition().y - temp->GetRect().getSize().y / 2 &&
	//				pN->getPosition().y <= temp->getPosition().y + temp->GetRect().getSize().y / 2)
	//			{
	//				NavGraph.removeNode(pN->Index());
	//			}
	//		}
	//	}
	//}
	//nodes = GraphHelper_DrawNode(NavGraph);
	//edges = GraphHelper_DrawEdge(NavGraph);
	//NavGraph.save("Testgrid.txt");*/

	//m_player->initAnimation();
	//m_player->getAnimatedSprite()->play(*m_player->getAnimation("idle"));

	return true;
}


/*	Called when changing state and old state exits */
void StartState::ExitState()
{
	m_core->m_GameMgr->SetState("GameState");
}


/* Parameter Deltatime
Handles State Update */
bool StartState::Update(float p_fDeltatime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
	{
		ExitState();
	}
	
	return true;
}
/*	Draws State*/
void StartState::Draw()
{
	
}

/*	Changes state to the states default Next State */
std::string StartState::Next()
{
	return "HEJ! FIXA MIG!!";
}


/* Returns True if Type == &p_type is same as StartState */
bool StartState::IsType(const std::string &p_sType)
{
	return m_sCurrentState.compare(p_sType) == 0;
}


/*	Returns Current State */
std::string StartState::GetCurrentState()
{
	return m_sCurrentState;
}