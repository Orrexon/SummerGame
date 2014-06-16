//Core.cpp
#include <iostream>
#include "Core.h"
#include "StartState.h"

Core::Core()
{
	m_GameMgr = new GameStateManager;
	m_collMgr = new CollisionManager;
}
Core::~Core()
{
	delete m_GameMgr;
	m_GameMgr = nullptr;
	delete m_collMgr;
	m_collMgr = nullptr;
}

bool Core::initialize()
{
	window.create(sf::VideoMode(500, 500), "SummerGame");
	m_GameMgr->Attach(new StartState(this));
	m_GameMgr->SetState("StartState");
	return true;
}

void Core::run()
{
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear(sf::Color::Black);
		updateDeltatime();
		m_GameMgr->Update(m_fdeltatime);
		window.display();
	}
}

void Core::updateDeltatime()
{
	m_timeSinceLastUpdate = m_clock.restart();

	m_fdeltatime = m_timeSinceLastUpdate.asSeconds();
	//std::cout << m_fdeltatime << std::endl;
	if (m_fdeltatime > 0.1f)
	{
		m_fdeltatime = 0.1f;
	}
}