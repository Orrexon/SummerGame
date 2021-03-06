//Level.cpp
#include "stdafx.h"
//#include "Level.h"

Level::Level(GameObjectManager* gameobjmgr, CollisionManager* collmgr) :NavGraph(false)
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
			sf::Sprite sprite = spritemanager->load("platformtiles.png", c.x, c.y, c.w, c.h);
			BoxCollider* collider = new BoxCollider(sf::Vector2f(static_cast<float>(x), static_cast<float>(y)),
				sf::Vector2f(static_cast<float>(c.w), static_cast<float>(c.h)));
			PlatformObject* platform = new PlatformObject(collider, collider->getPosition(), sprite);

			m_collMgr->Attach(collider);
			m_gameObjMgr->attach(platform);

			x += m_width;
		}
		y += m_height;
	}
	//load the graph and remove the nodes that are inside of the platforms
	GraphHelper_CreateGrid(NavGraph, x, y, 25, 50);
	PlatformObject* temp;
	SparseGraph<NavGraphNode<>, NavGraphEdge>::ConstNodeIterator ConstNodeItr(NavGraph);
	for (const SparseGraph<NavGraphNode<>, NavGraphEdge>::NodeType* pN = ConstNodeItr.begin();
		!ConstNodeItr.end();
		pN = ConstNodeItr.next())
	{
		for (int i = 0; i < m_gameObjMgr->getGameObjVecSize(); ++i)
		{
			if (temp = dynamic_cast<PlatformObject*>(m_gameObjMgr->getGameObject(i)))
			{
				if (pN->getPosition().x <= temp->getPosition().x + dynamic_cast<BoxCollider*>(temp->getCollider())->GetExtention().x / 2 &&
					pN->getPosition().x >= temp->getPosition().x - dynamic_cast<BoxCollider*>(temp->getCollider())->GetExtention().x / 2 &&
					pN->getPosition().y >= temp->getPosition().y - dynamic_cast<BoxCollider*>(temp->getCollider())->GetExtention().y / 2 &&
					pN->getPosition().y <= temp->getPosition().y + dynamic_cast<BoxCollider*>(temp->getCollider())->GetExtention().y / 2)
				{
					if (pN->Index() > -1)
					NavGraph.removeNode(pN->Index());
				}
			}
		}
	}
	nodes = GraphHelper_DrawNode(NavGraph);
	edges = GraphHelper_DrawEdge(NavGraph);
	NavGraph.save("Testgrid.txt");
	stream.close();
}