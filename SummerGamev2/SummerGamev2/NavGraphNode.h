//NavGraphNode.h
#pragma once
#include <SFML\Graphics.hpp>
#include "GraphNode.h"

template<class extra_info = void*>
class NavGraphNode : public GraphNode
{
public:
	NavGraphNode() :m_extraInfo(extra_info()){}
	
	NavGraphNode(int index, sf::Vector2f position) :GraphNode(index),
	m_position(position),
	m_extraInfo(extra_info())
	{}

	NavGraphNode(std::ifstream& stream) :m_extraInfo(extra_info())
	{
		char buffer[50];
		stream >> buffer >> m_iIndex >> buffer >> m_position.x >> buffer >> m_position.y;
	}

	virtual ~NavGraphNode(){}

	sf::Vector2f getPosition()const{ return m_position; }
	void setPosition(sf::Vector2f pos) { m_position = pos; }

	extra_info extraInfo()const{ return m_extraInfo; }
	void setExtraInfo(extra_info info){ m_extraInfo = info; }

	friend std::ostream& operator<<(std::ostream& os, const NavGraphNode& n)
	{
		os << "Index: " << n.m_iIndex << " PosX: " << n.m_position.x << " PosY: " << n.m_position.y << std::endl;
		return os;
	}

protected:
	sf::Vector2f m_position;

	//some extra info related to the node, such as items 
	//to check for status during search
	extra_info m_extraInfo;
};