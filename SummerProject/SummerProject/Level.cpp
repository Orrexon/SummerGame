//Level.cpp
#include "Level.h"

Level::Level(GameObjectManager* gameobjmgr, CollisionManager* collmgr)
{
	m_gameObjMgr = gameobjmgr;
	m_collMgr = collmgr;
	m_height = 0;
	m_width = 0;
	m_playerStartPos = { 0.f, 0.f };
}

bool Level::load(std::string filename, SpriteManager* spritemanager)
{
	std::ifstream stream(filename);
	if (!stream.is_open())
	{
		return false;
	}

	std::string row;
	unsigned int coord_count = 0;
	stream >> m_mapFilename;
	stream >> coord_count >> m_width >> m_height;
	std::getline(stream, row);
	for (size_t i = 0; i < coord_count; i++)
	{
		std::getline(stream, row);
		std::stringstream ss(row);
		std::string ch;
		coords co_ords;

		ss >> ch;
		ss >> co_ords.x;
		ss >> co_ords.y;
		ss >> co_ords.w;
		ss >> co_ords.h;

		m_coordinates.insert(std::pair<char, coords>(ch[0], co_ords));
	}

	unsigned int x = 0;
	unsigned int y = 0;
	while (!stream.eof())
	{
		std::getline(stream, row, '\n');
		if (row.length() == 0)
		{
			continue;
		}
		x = 0;
		for (size_t i = 0; i < row.length(); i++)
		{
			if (row[i] == '0')
			{
				x += m_width;
				continue;
			}
			else if (row[i] == 'P')
			{
				m_playerStartPos.x = x;
				m_playerStartPos.y = y;
				x += m_width;
				continue;
			}

			else if (row[i] == 'B')
			{
				m_aBeggarStartPos.push_back(sf::Vector2f(x, y));
				x += m_width;
				continue;
			}

			else if (row[i] == 'S')
			{
				m_aSalesmanStartPos.push_back(sf::Vector2f(x, y));
				x += m_width;
				continue;
			}

			std::map<char, coords>::iterator it = m_coordinates.find(row[i]);
			if (it == m_coordinates.end())
			{
				continue;
			}

			coords& c = it->second;
			sf::Sprite sprite = spritemanager->load(filename, c.x, c.y, c.w, c.h);
			BoxCollider* collider = new BoxCollider(sf::Vector2f(c.x, c.y), sf::Vector2f(c.w, c.h));
			PlatformObject* platform = new PlatformObject(collider, sf::Vector2f(c.x, c.y), sprite);

			m_collMgr->Attach(collider);
			m_gameObjMgr->attach(platform);

			x += m_width;
		}
		y += m_height;
	}
	stream.close();
}