//core.h
#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "GameStateManager.h"
#include "CollisionManager.h"
#include "InputManager.h"

class Core
{
public:
	Core();
	~Core();

	bool initialize();

	void run();

	void updateDeltatime();


	GameStateManager* m_GameMgr;
	CollisionManager* m_collMgr;
	InputManager* m_inputMgr;
	float m_fdeltatime;
	sf::Clock m_clock;
	sf::Time m_timeSinceLastUpdate;
	sf::RenderWindow window;
};