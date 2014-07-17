//Core.cpp
#include <iostream>
#include "Core.h"
#include "StartState.h"

Core::Core()
{
	m_GameMgr = new GameStateManager;
	m_collMgr = new CollisionManager;
	m_inputMgr = new InputManager;
	m_GameObjMgr = new GameObjectManager;
	m_spriteMgr = new SpriteManager("../data/sprites/");
	m_level = new Level(m_GameObjMgr, m_collMgr);
	m_view = nullptr;

	m_fdeltatime = 0.f;
	m_clock.restart();
}
Core::~Core()
{
	if (m_GameMgr != nullptr)
	{
		delete m_GameMgr;
		m_GameMgr = nullptr;
	}
	if (m_collMgr != nullptr)
	{
		delete m_collMgr;
		m_collMgr = nullptr;
	}
	if (m_inputMgr != nullptr)
	{
		delete m_inputMgr;
		m_inputMgr = nullptr;
	}
	if (m_GameObjMgr != nullptr)
	{
		delete m_GameObjMgr;
		m_GameObjMgr = nullptr;
	}
	if (m_spriteMgr != nullptr)
	{
		delete m_spriteMgr;
		m_spriteMgr = nullptr;
	}
	if (m_level != nullptr)
	{
		delete m_level;
		m_level = nullptr;
	}
	if (m_view != nullptr)
	{
		delete m_view;
		m_view = nullptr;
	}
}

bool Core::initialize()
{
	window.create(sf::VideoMode(1000, 945), "SummerGame");
	sf::View w(sf::FloatRect(0,0,1000,945));
	m_view = new View(w);
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
			{
				window.close();
			}
			m_inputMgr->UpdateEvents(event);
		}
		window.clear(sf::Color::Black);
		updateDeltatime();
		m_GameMgr->Update(m_fdeltatime);
		m_GameMgr->Draw();
		window.display();

		m_inputMgr->PostUpdateKeyboard();
		m_inputMgr->PostUpdateMouse();
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

