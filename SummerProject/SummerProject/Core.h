//core.h
#pragma once
#include "SFML\System.hpp"
#include "SFML\Graphics.hpp"
#include "GameStateManager.h"


class Core
{
public:
	Core();
	~Core();

	bool initialize();

	void run();

	void updateDeltatime();

	GameStateManager* m_GameMgr;
	float m_fdeltatime;
	sf::Clock m_clock;
	sf::Time m_timeSinceLastUpdate;
	sf::RenderWindow window;
};