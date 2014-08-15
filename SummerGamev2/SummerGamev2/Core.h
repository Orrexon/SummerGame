//core.h
#pragma once
//#include "SFML\System.hpp"
//#include "SFML\Graphics.hpp"
//#include "GameStateManager.h"
//#include "CollisionManager.h"
//#include "InputManager.h"
//#include "GameObjectManager.h"
//#include "SpriteManager.h"
//#include "Level.h"
//#include "View.h"
//class GameStateManager;
//class CollisionManager;
//class InputManager;
//class SpriteManager;
//class GameObjectManager;
//class Level;
//class View;

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
	GameObjectManager* m_GameObjMgr;
	SpriteManager* m_spriteMgr;
	Level* m_level;
	View* m_view;
	float m_fdeltatime;
	sf::Clock m_clock;
	sf::Time m_timeSinceLastUpdate;
	sf::RenderWindow window;
};