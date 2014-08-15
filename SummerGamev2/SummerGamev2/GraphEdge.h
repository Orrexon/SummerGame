//GraphEdge.h

#pragma once
#include <ostream>
#include <fstream>

class GraphEdge
{
public:
	GraphEdge(int from, int to, double cost) 
		:m_iFrom(from)
		, m_iTo(to)
		, m_dCost(cost){}
	GraphEdge(int from, int to)
		:m_iFrom(from)
		, m_iTo(to)
		, m_dCost(1.0){}

	//invalid indices to deafault ctor
	GraphEdge()
		:m_iFrom(-1)
		, m_iTo(-1)
		, m_dCost(1.0){}

	//stream ctor
	GraphEdge(std::ifstream& stream)
	{
		char buffer[50];
		stream >> buffer >> m_iFrom >> buffer >> m_iTo >> buffer >> m_dCost;
	}
	//if there are specialized edges
	virtual ~GraphEdge(){}

	int From()const{ return m_iFrom; }
	void setFrom(int newIndex){ m_iFrom = newIndex; }

	int To()const{ return m_iTo; }
	void setTo(int newIndex){ m_iTo = newIndex; }

	double Cost()const{ return m_dCost; }
	void setCost(double newCost){ m_dCost = newCost; }

	bool operator==(const GraphEdge& rhs)
	{
		return rhs.m_iFrom == this->m_iFrom &&
			rhs.m_iTo == this->m_iTo &&
			rhs.m_dCost == this->m_dCost;
	}

	bool operator!=(const GraphEdge& rhs)
	{
		return !(*this == rhs);
	}

	//for reading and writing to streams
	friend std::ostream& operator<<(std::ostream& os, const GraphEdge& e)
	{
		os << "m_iFrom: " << e.m_iFrom << " m_iTo: " << e.m_iTo
			<< " m_dCost: " << e.m_dCost << std::endl;
		return os;
	}

protected:
	int m_iFrom;
	int m_iTo;

	double m_dCost;

};