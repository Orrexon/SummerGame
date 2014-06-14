//GameStateManager.cpp
#include <iostream>
#include "GameStateManager.h"

GameStateManager::GameStateManager()
{
	m_pCurrentState = nullptr;
}

GameStateManager::~GameStateManager()
{
	
	for (auto it : m_aStates)
	{
		if (it != nullptr)
		{
			delete it;
			it = nullptr;
		}
	}
	
}

/* Returns Current State as String */
std::string GameStateManager::CurrentState(){ return m_pCurrentState->GetCurrentState(); }
/* Attaches new State to StateManager */
void GameStateManager::Attach(State *p_pState)
{
	m_aStates.push_back(p_pState);
}
/* Calls CurrentStates Update */
void GameStateManager::Update(float p_fDeltatime)
{
	m_pCurrentState->Update(p_fDeltatime);
}
/* Calls CurrentStates Draw */
void GameStateManager::Draw(){}
/* Changes CurrentState into string parameter*/
void GameStateManager::SetState(const std::string &p_sType)
{
	for (auto it : m_aStates)
	{
		if (it->IsType(p_sType))
		{
			m_pCurrentState = it;
			m_pCurrentState->EnterState();
		}
		else { std::cout << "GameStateManager::SetState(string), no state like '" << p_sType << "'" << std::endl; }
	}
}
/* Changed State into States Default Next() */
void GameStateManager::ChangeState(){}
/* Returns True while running */
bool GameStateManager::IsRunning(){ return true;/*need fixing*/ }

State* GameStateManager::GetCurrentState(){ return m_pCurrentState; }