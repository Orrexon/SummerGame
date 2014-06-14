//GameStateManager.h
#pragma once
#include "State.h"
#include <vector>

class GameStateManager
{
public:
	GameStateManager();
	
	~GameStateManager();
	
	/* Returns Current State as String */
	std::string CurrentState();
	/* Attaches new State to StateManager */
	void Attach(State *p_pState);
	/* Calls CurrentStates Update */
	void Update(float p_fDeltatime);
	/* Calls CurrentStates Draw */
	void Draw();
	/* Changes CurrentState into string parameter*/
	void SetState(const std::string &p_sType);
	/* Changed State into States Default Next() */
	void ChangeState();
	/* Returns True while running */
	bool IsRunning();

	State* GetCurrentState();

private:
	/* Vector of States*/
	std::vector<State*> m_aStates;
	/* Current State Pointer*/
	State *m_pCurrentState;

};