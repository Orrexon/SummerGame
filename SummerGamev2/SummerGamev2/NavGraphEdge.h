//NavGraphEdge.h

#pragma once
#include "GraphEdge.h"

class NavGraphEdge : public GraphEdge
{
public:
	enum
	{
		normal =	0,
		run =		1 << 0,
		jump =		1 << 1,
		fall =		1 << 2
	};
public:
	NavGraphEdge(int from, int to, double cost, int flags = 0, int id = -1)
		:GraphEdge(from, to, cost), m_iFlags(flags), m_iIDofIntersectingEntity(id)
	{}

	NavGraphEdge(std::ifstream stream)
	{
		char buffer[50];
		stream >> buffer >> m_iFrom >> buffer >> m_iTo >> buffer >> m_dCost;
		stream >> buffer >> m_iFlags >> buffer >> m_iIDofIntersectingEntity;
	}

	int Flags()const{ return m_iFlags; }
	void setFlags(int flag){ m_iFlags = flag; }

	int iIDofIntersectingEntity()const{ return m_iIDofIntersectingEntity; }
	void setIDofIntersectingEntity(int id){ m_iIDofIntersectingEntity = id; }

	friend std::ostream& operator<<(std::ostream & os, const NavGraphEdge& e)
	{
		os << "m_iFrom: " << e.m_iFrom << " m_iTo: " << e.m_iTo
			<< " m_dCost: " << e.m_dCost << " m_iFlags: " << e.m_iFlags
			<< " ID: " << e.m_iIDofIntersectingEntity << std::endl;

		return os;
	}
protected:
	int m_iFlags;

	int m_iIDofIntersectingEntity;
};