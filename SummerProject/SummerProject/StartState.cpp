//startstate.cpp
#include <iostream>
#include "StartState.h"



StartState::StartState(Core* p_Core )
{ 
	m_sCurrentState = "StartState";
	m_GameStateManager = p_Core->m_GameMgr;
	m_core = p_Core;
	
}




/*	Called upon entering state */
bool StartState::EnterState()
{
	Update(m_core->m_fdeltatime);
	return true;
}


/*	Called when changing state and old state exits */
void StartState::ExitState(){}


/* Parameter Deltatime
Handles State Update */
bool StartState::Update(float p_fDeltatime)
{
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