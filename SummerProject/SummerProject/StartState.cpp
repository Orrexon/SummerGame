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
	
	
	GraphHelper_CreateGrid(NavGraph, 1000, 1000, 5, 5);
	BoxCollider* collider = new BoxCollider (sf::Vector2f(50, 50), sf::Vector2f(50, 66));
	m_player = new Player(collider, sf::Vector2f(50, 50), m_core->m_inputMgr,
		m_core->m_collMgr, m_core->m_GameObjMgr);
	BoxCollider* collider2 = new BoxCollider(sf::Vector2f(200, 100), sf::Vector2f(100, 100));
	ground0 = new PlatformObject(collider2, sf::Vector2f(200, 100));
	BoxCollider* collider3 = new BoxCollider(sf::Vector2f(250, 500), sf::Vector2f(500, 100));
	ground = new PlatformObject(collider3, sf::Vector2f(250, 500));
	CircleCollider* collider4 = new CircleCollider(sf::Vector2f(300, 200), 10.f);
	bullet0 = new Bullet(collider4, sf::Vector2f(300, 200));
	CircleCollider* collider5 = new CircleCollider(sf::Vector2f(300, 200), 10.f);
	bullet1 = new Bullet(collider5, sf::Vector2f(600, 200));
	CircleCollider* collider6 = new CircleCollider(sf::Vector2f(300, 300), 10.f);
	bullet2 = new Bullet(collider6, sf::Vector2f(300, 300));
	BoxCollider* collider7 = new BoxCollider(sf::Vector2f(500, 400), sf::Vector2f(50, 40));
	salesman = new SalesMan(collider7, sf::Vector2f(500, 400));

	m_player->initTestbody();
	
	bullet0->setVelocity(sf::Vector2f(2.f, 0.f));
	bullet1->setVelocity(sf::Vector2f(-2.f, 0.f));
	
	m_core->m_GameObjMgr->attach(ground);
	m_core->m_GameObjMgr->attach(ground0);
	m_core->m_GameObjMgr->attach(bullet0);
	m_core->m_GameObjMgr->attach(bullet1);
	m_core->m_GameObjMgr->attach(bullet2);
	m_core->m_GameObjMgr->attach(salesman);

	m_core->m_collMgr->Attach(m_player->getCollider());
	m_core->m_collMgr->Attach(ground0->getCollider());
	m_core->m_collMgr->Attach(ground->getCollider());
	m_core->m_collMgr->Attach(bullet0->getCollider());
	m_core->m_collMgr->Attach(bullet1->getCollider());
	m_core->m_collMgr->Attach(bullet2->getCollider());
	m_core->m_collMgr->Attach(salesman->getCollider());

	m_core->m_GameObjMgr->initTestBodies();

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
	m_player->getAnimatedSprite()->update(sf::seconds(p_fDeltatime));
	m_player->update(p_fDeltatime);
	m_core->m_GameObjMgr->update(p_fDeltatime);
	m_core->m_collMgr->Update();
	m_core->m_collMgr->RemoveColliders();
	m_core->m_GameObjMgr->removeObjects();
	
	//Draw();
	return true;
}
/*	Draws State*/
void StartState::Draw()
{
	m_core->window.draw(ground->GetRect());
	m_core->window.draw(m_player->GetRect());
	m_core->window.draw(ground0->GetRect());
	m_core->m_GameObjMgr->draw(m_core->window);
	
	//testing spritemanager
	sf::Sprite sp = m_core->m_spriteMgr->load("optimusprime.png", 0,0,70,70);
	sp.setOrigin(70 / 2, 70 / 2);
	sp.setPosition(500, 500);
	m_core->window.draw(sp);
	m_core->window.draw(*m_player->getAnimatedSprite());

	std::vector<sf::CircleShape> nodes = GraphHelper_DrawNode(NavGraph);
	std::vector<sf::VertexArray> edges = GraphHelper_DrawEdge(NavGraph);
	for ( auto& it : nodes)
	{
		m_core->window.draw(it);
	}
	for (auto& it : edges)
	{
		m_core->window.draw(it);
	}
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