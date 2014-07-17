//Level.h
#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <map>
#include "BoxCollider.h"
#include "PlatformObject.h"
#include "SpriteManager.h"
#include "GameObjectManager.h"
#include "CollisionManager.h"



class Level
{
	struct coords
	{
		int x, y, w, h;
	};
public:
	Level(GameObjectManager* gameobjmgr, CollisionManager* collmgr);
	~Level(){}

	bool load(std::string filename, SpriteManager* spritemgr);

	sf::Vector2f getPlayerStartPosition() { return m_playerStartPos; }
	sf::Vector2f getBeggarStartPosition(int i) { return m_aBeggarStartPos[i]; }
	sf::Vector2f getSalesmanStartPosition(int i) { return m_aSalesmanStartPos[i]; }

private:
	sf::Vector2f m_playerStartPos;
	std::vector<sf::Vector2f> m_aBeggarStartPos, m_aSalesmanStartPos;
	std::string m_mapFilename;
	SpriteManager* m_spriteMgr;
	std::map<char, coords> m_coordinates;
	unsigned int m_width, m_height;
	GameObjectManager* m_gameObjMgr;
	CollisionManager* m_collMgr;
};