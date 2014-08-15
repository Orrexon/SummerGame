//GameState.cpp
#include "stdafx.h"
//#include "GameState.h"

GameState::GameState(Core* core) :NavGraph(false)
{
	m_core = core;
	m_sCurrentState = "GameState";
}

bool GameState::EnterState()
{
	printf("\nGameState::EnterState()");
	/*m_core->m_level->load("../data/map/map.txt", m_core->m_spriteMgr);*/
	BoxCollider* collider = new BoxCollider(m_core->m_level->getPlayerStartPosition(), sf::Vector2f(50, 64));
	m_player = new Player(collider, m_core->m_level->getPlayerStartPosition(), m_core->m_inputMgr,
		m_core->m_collMgr, m_core->m_GameObjMgr);

	for (size_t i = 0; i < m_core->m_level->getSalesManStartPosVec().size(); ++i)
	{
		BoxCollider* sale = new BoxCollider(m_core->m_level->getSalesmanStartPosition(i), sf::Vector2f(50, 110));
		SalesMan* saleobj = new SalesMan(sale, m_core->m_level->getSalesmanStartPosition(i));
		m_core->m_collMgr->Attach(saleobj->getCollider());
		m_core->m_GameObjMgr->attach(saleobj);
	}
		//m_player->initTestbody();

	m_core->m_collMgr->Attach(m_player->getCollider());


	m_core->m_GameObjMgr->initTestBodies();
	m_core->m_GameObjMgr->initAnimations();
	m_player->initAnimation();
	m_player->getAnimatedSprite()->play(*m_player->getAnimation("idle"));
	return true;
}
/*	Called when changing state and old state exits */
void GameState::ExitState(){}
/* Parameter Deltatime
Handles State Update */
bool GameState::Update(float p_fDeltatime)
{
	sf::Vector2f playerPos = m_player->getPosition();
	m_player->getAnimatedSprite()->update(sf::seconds(p_fDeltatime));
	m_core->m_GameObjMgr->updateAnimatedSprites(p_fDeltatime);
	m_player->update(p_fDeltatime);
	m_core->m_GameObjMgr->update(p_fDeltatime, m_core->m_view->getOwnView().getCenter());
	m_core->m_collMgr->Update(m_core->m_view->getOwnView().getCenter());
	m_core->m_collMgr->RemoveColliders();
	m_core->m_GameObjMgr->removeObjects();
	m_core->m_view->update(p_fDeltatime, playerPos);
	return true;
}
/*	Draws State*/
void GameState::Draw()
{
	m_core->window.setView(m_core->m_view->getOwnView());
	m_core->m_GameObjMgr->draw(m_core->window);

	//testing spritemanager
	sf::Sprite sp = m_core->m_spriteMgr->load("optimusprime.png", 0, 0, 70, 70);
	sp.setOrigin(70 / 2, 70 / 2);
	sp.setPosition(500, 500);
	m_core->window.draw(sp);
	m_core->window.draw(*m_player->getAnimatedSprite());

	//draw the graph
	/*for (auto& it : m_core->m_level->getNodes())
	{
		m_core->window.draw(it);
	}
	for (auto& it : m_core->m_level->getEdges())
	{
		m_core->window.draw(it);
	}*/
}
/*	Changes state to the states default Next State */
std::string GameState::Next()
{
	return "Hej, fixa mig ;)";
}
/* Returns True if Type == &p_type is same as State */
bool GameState::IsType(const std::string &p_sType)
{
	return m_sCurrentState.compare(p_sType) == 0;
}
/*	Returns Current State */
std::string GameState::GetCurrentState()
{
	return m_sCurrentState;
}