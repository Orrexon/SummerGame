//startstate.cpp
#include <iostream>
#include "StartState.h"



StartState::StartState(Core* p_Core )
{ 
	m_sCurrentState = "StartState";
	m_core = p_Core;
	
}




/*	Called upon entering state */
bool StartState::EnterState()
{
	BoxCollider* collider = new BoxCollider (sf::Vector2f(50, 50), sf::Vector2f(100, 100));
	m_player = new Player(collider, sf::Vector2f(50, 50));
	m_player->initTestbody();
	Update(m_core->m_fdeltatime);
	return true;
}


/*	Called when changing state and old state exits */
void StartState::ExitState(){}


/* Parameter Deltatime
Handles State Update */
bool StartState::Update(float p_fDeltatime)
{
	m_player->update(p_fDeltatime);
	Draw();
	return true;
}
/*	Draws State*/
void StartState::Draw()
{
	sf::CircleShape sh;
	sh.setFillColor(sf::Color::Green);
	sh.setPosition(50, 100);
	sh.setRadius(25.f);
	m_core->window.draw(sh);
	m_core->window.draw(m_player->GetRect());
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