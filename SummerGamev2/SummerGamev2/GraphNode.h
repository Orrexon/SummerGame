//GraphNode.h

#pragma once

class GraphNode
{
public:
	//Invalid node index
	GraphNode() :m_iIndex(-1){}
	GraphNode(int index) :m_iIndex(index){}

	virtual ~GraphNode(){}

	int Index()const { return m_iIndex; }
	void setIndex(int index){ m_iIndex = index; }

protected:
	int m_iIndex;
};