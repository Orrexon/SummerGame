//Core.cpp

#include "Core.h"
#include "StartState.h"

Core::Core()
{
	m_GameMgr = new GameStateManager;
}
Core::~Core()
{
	delete m_GameMgr;
	m_GameMgr = nullptr;
}

bool Core::initialize()
{
	m_GameMgr->Attach(new StartState(this));
	m_GameMgr->SetState("StartState");
	window.create(sf::VideoMode(500, 500), "SummerGame");
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
	//cout << m_fDeltaTime << endl;
	if (m_fdeltatime > 0.1f)
	{
		m_fdeltatime = 0.1f;
	}
}