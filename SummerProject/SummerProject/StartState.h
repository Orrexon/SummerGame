// State.h
#pragma once
#include "State.h"
#include "Core.h"


class StartState : public State
{
public:
	StartState(Core* core);

	virtual ~StartState(){};
	/*	Called upon entering state */
	virtual bool EnterState();
	/*	Called when changing state and old state exits */
	virtual void ExitState();
	/* Parameter Deltatime
	Handles State Update */
	virtual bool Update(float p_fDeltatime);
	/*	Draws State*/
	virtual void Draw();
	/*	Changes state to the states default Next State */
	virtual std::string Next();
	/* Returns True if Type == &p_type is same as StartState */
	virtual bool IsType(const std::string &p_sType);
	/*	Returns Current State */
	virtual std::string GetCurrentState();

private:
	GameStateManager* m_GameStateManager;
	sf::RenderWindow window;
	Core* m_core;
};
