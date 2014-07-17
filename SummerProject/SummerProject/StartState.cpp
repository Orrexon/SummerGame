//startstate.cpp
#include <iostream>

#include "StartState.h"




StartState::StartState(Core* p_Core) :NavGraph(false)
{
	m_sCurrentState = "StartState";
	m_core = p_Core;

}




/*	Called upon entering state */
bool StartState::EnterState()
{
	
	m_core->m_level->load("../data/map/map.txt", m_core->m_spriteMgr);
	/*GraphHelper_CreateGrid(NavGraph, 1000, 1000, 25, 25);
	Graph_SearchAStar<SparseGraph<NavGraphNode<>, NavGraphEdge>, Heuristic_Euclid> Astar(NavGraph, 143, 22);*/
	BoxCollider* collider = new BoxCollider(m_core->m_level->getPlayerStartPosition(), sf::Vector2f(50, 64));
	m_player = new Player(collider, m_core->m_level->getPlayerStartPosition(), m_core->m_inputMgr,
		m_core->m_collMgr, m_core->m_GameObjMgr);


	//m_player->initTestbody();

	m_core->m_collMgr->Attach(m_player->getCollider());

	/*PlatformObject* temp;
	SparseGraph<NavGraphNode<>, NavGraphEdge>::ConstNodeIterator ConstNodeItr(NavGraph);
	for (const SparseGraph<NavGraphNode<>, NavGraphEdge>::NodeType* pN = ConstNodeItr.begin();
		!ConstNodeItr.end();
		pN = ConstNodeItr.next())
	{
		for (int i = 0; i < m_core->m_GameObjMgr->getGameObjVecSize(); ++i)
		{
			if (temp = dynamic_cast<PlatformObject*>(m_core->m_GameObjMgr->getGameObject(i)))
			{
				if (pN->getPosition().x <= temp->getPosition().x + temp->GetRect().getSize().x / 2 &&
					pN->getPosition().x >= temp->getPosition().x - temp->GetRect().getSize().x / 2 &&
					pN->getPosition().y >= temp->getPosition().y - temp->GetRect().getSize().y / 2 &&
					pN->getPosition().y <= temp->getPosition().y + temp->GetRect().getSize().y / 2)
				{
					NavGraph.removeNode(pN->Index());
				}
			}
		}
	}
	nodes = GraphHelper_DrawNode(NavGraph);
	edges = GraphHelper_DrawEdge(NavGraph);
	NavGraph.save("Testgrid.txt");*/

	m_player->initAnimation();
	m_player->getAnimatedSprite()->play(*m_player->getAnimation("idle"));

	return true;
}


/*	Called when changing state and old state exits */
void StartState::ExitState(){}


/* Parameter Deltatime
Handles State Update */
bool StartState::Update(float p_fDeltatime)
{
	sf::Vector2f playerPos = m_player->getPosition();
	m_player->getAnimatedSprite()->update(sf::seconds(p_fDeltatime));
	m_player->update(p_fDeltatime);
	m_core->m_GameObjMgr->update(p_fDeltatime);
	m_core->m_collMgr->Update();
	m_core->m_collMgr->RemoveColliders();
	m_core->m_GameObjMgr->removeObjects();
	m_core->m_view->update(p_fDeltatime, playerPos);

	return true;
}
/*	Draws State*/
void StartState::Draw()
{
	m_core->window.setView(m_core->m_view->getOwnView());
	//m_core->window.draw(m_player->GetRect());
	m_core->m_GameObjMgr->draw(m_core->window);

	//testing spritemanager
	sf::Sprite sp = m_core->m_spriteMgr->load("optimusprime.png", 0, 0, 70, 70);
	sp.setOrigin(70 / 2, 70 / 2);
	sp.setPosition(500, 500);
	m_core->window.draw(sp);
	m_core->window.draw(*m_player->getAnimatedSprite());

	//draw the graph
	/*for (auto& it : nodes)
	{
		m_core->window.draw(it);
	}
	for (auto& it : edges)
	{
		m_core->window.draw(it);
	}*/
}

/*	Changes state to the states default Next State */
std::string StartState::Next()
{
	return "HEJ! FIXA MIG!!";
}


/* Returns True if Type == &p_type is same as StartState */
bool StartState::IsType(const std::string &p_sType)
{
	return p_sType.compare("StartState") == 0;
}


/*	Returns Current State */
std::string StartState::GetCurrentState()
{
	return m_sCurrentState;
}