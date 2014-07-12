//graphalgorithms.h
#pragma once
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <SFML\Graphics.hpp>
#include "SparseGraph.h"
#include "PriorityQueue.h"

//Class to implement a deapth first search, DFS
template<class graph_type>
class Graph_SearchDFS
{
private:
	enum {visited, unvisited, no_parent_assigned};

	//typedefs for the edge and node types used by the graph
	typedef typename graph_type::EdgeType Edge;
	typedef typename graph_type::NodeType Node;

public:
	Graph_SearchDFS(const graph_type& graph,
		int source,
		int target = -1)
		:m_Graph(graph),
		m_iSource(source),
		m_iTarget(target),
		m_bFound(false),
		m_Visited(m_graph.numNodes(), unvisited),
		m_Route(m_Graph.numNodes(), no_parent_assigned)
	{
		m_bFound = Search();
	}
	//return the edge vector
	std::vector<const Edge*> getSearchTree()const { return m_SpanningTree; }

	bool Found()const { return m_bFound; }

	//returns a vector of node indexes that comprise the shortest path
	//from source to target
	std::list<int> getPathToTarget()const;
private:
	//a ref to the graph to be searched
	const graph_type& m_Graph;

	//this records the indexes of all the nodes that are visited
	//as the search progresses
	std::vector<int> m_Visited;

	//this holds the route taken to the target
	std::vector<int> m_Route;

	//as the this holds all the edges examined.
	//THIS IS ONLY USEFUL IF YOU WANT TO DRAW THE EXAMINED EDGES
	std::vector<const Edge*> m_SpanningTree;

	int m_iSource, m_iTarget;

	bool m_bFound;

	//This performs the DFS search
	bool Search();
};

template<class graph_type>
class Graph_SearchBFS
{
private:

	enum { visited, unvisited, no_parent_assigned };

	//create a typedef for the edge type used by the graph
	typedef typename graph_type::EdgeType Edge;

public:
	Graph_SearchBFS(const graph_type& graph,
		int source,
		int target = -1)
		:m_Graph(graph),
		m_iSource(source),
		m_iTarget(target),
		m_bFound(false),
		m_Visited(m_graph.numNodes(), unvisited),
		m_Route(m_Graph.numNodes(), no_parent_assigned)
	{
		m_bFound = Search();
	}
	//return the edge vector
	std::vector<const Edge*> getSearchTree()const { return m_SpanningTree; }

	bool Found()const { return m_bFound; }

	//returns a vector of node indexes that comprise the shortest path
	//from source to target
	std::list<int> getPathToTarget()const;
private:
	//a ref to the graph to be searched
	const graph_type& m_Graph;

	//this records the indexes of all the nodes that are visited
	//as the search progresses
	std::vector<int> m_Visited;

	//this holds the route taken to the target
	std::vector<int> m_Route;

	//as the this holds all the edges examined.
	//THIS IS ONLY USEFUL IF YOU WANT TO DRAW THE EXAMINED EDGES
	std::vector<const Edge*> m_SpanningTree;

	int m_iSource, m_iTarget;

	bool m_bFound;

	//This performs the BFS search is similar to the DFS except It uses
	//a first in first out queue instead of a stack
	bool Search();
};

//Graph Search Dijkstra
//Shortest path from source to target

template<class graph_type>
class Graph_SearchDijkstra
{
private:

	typedef typename graph_type::EdgeType Edge;

public:
	Graph_SearchDijkstra(const graph_type& graph,
		int source,
		int target = -1)
		:m_Graph(graph),
		m_ShortestPathTree(graph.numNodes()),
		m_SearchFrontier(graph.numNodes()),
		m_CostToThisNode(graph.numNodes()),
		m_iSource(source),
		m_iTarget(target)
	{
		Search();
	}

	//returns the vector of edges that defines the SPT. If a target was given
	//in the constructor then this will be an SPT comprising of all the nodes
	//examined before the target was found, else it will contain all the nodes
	//in the graph.
	std::vector<const Edge*> GetSPT()const{ return m_ShortestPathTree; }

	//returns a vector of node indexes that comprise the shortest path
	//from the source to the target. It calculates the path by working
	//backwards through the SPT from the target node.
	std::list<int> getPathToTarget()const;

	//returns the total cost to the target
	double getCostToTarget()const{ return m_CostToThisNode[m_iTarget]; }

	//returns the total cost to the given node
	double getCostToNode(unsigned int nd)const{ return m_CostToThisNode[nd]; }

private:
	const graph_type& m_Graph;

	//this vector contains the edges that comprise the shortest path tree -
	//a directed subtree of the graph that encapsulates the best paths from 
	//every node on the SPT to the source node.
	std::vector<const Edge*>      m_ShortestPathTree;

	//this is indexed into by node index and holds the total cost of the best
	//path found so far to the given node. For example, m_CostToThisNode[5]
	//will hold the total cost of all the edges that comprise the best path
	//to node 5, found so far in the search (if node 5 is present and has 
	//been visited)
	std::vector<double>            m_CostToThisNode;

	//this is an indexed (by node) vector of 'parent' edges leading to nodes 
	//connected to the SPT but that have not been added to the SPT yet. This is
	//a little like the stack or queue used in BST and DST searches.
	std::vector<const Edge*>     m_SearchFrontier;

	int                           m_iSource;
	int                           m_iTarget;

	void Search();
};

//Graph A-Star
template<class graph_type, class heuristic>
class Graph_SearchAStar
{
private:

	//create a typedef for the edge type used by the graph
	typedef typename graph_type::EdgeType Edge;

public:
	Graph_SearchAStar(graph_type& graph,
		int source,
		int target = -1)
		:m_Graph(graph),
		m_ShortestPathTree(graph.numNodes()),
		m_SearchFrontier(graph.numNodes()),
		m_GCosts(graph.numNodes(), 0.0),
		m_FCosts(graph.numNodes(), 0.0),
		m_iSource(source),
		m_iTarget(target)
	{
		Search();
	}

	//returns the vector of edges that the algorithm has examined
	std::vector<const Edge*> GetSPT()const{ return m_ShortestPathTree; }

	//returns a vector of node indexes that comprise the shortest path
	//from the source to the target
	std::list<int> getPathToTarget()const;

	//returns the total cost to the target
	double getCostToTarget()const{ return m_GCosts[m_iTarget]; }

private:

	const graph_type&              m_Graph;

	//indexed into my node. Contains the 'real' accumulative cost to that node
	std::vector<double>             m_GCosts;

	//indexed into by node. Contains the cost from adding m_GCosts[n] to
	//the heuristic cost from n to the target node. This is the vector the
	//iPQ indexes into.
	std::vector<double>             m_FCosts;

	std::vector<const Edge*>       m_ShortestPathTree;
	std::vector<const Edge*>       m_SearchFrontier;

	int                            m_iSource;
	int                            m_iTarget;

	//the A* search algorithm
	void Search();

};

class Heuristic_Euclid
{
public:

	Heuristic_Euclid(){}

	//calculate the straight line distance from node nd1 to node nd2
	template <class graph_type>
	static double Calculate(const graph_type& G, int nd1, int nd2)
	{
		sf::Vector2f vFrom = G.GetNode(nd1).getPosition(););
		sf::Vector2f vTo = G.GetNode(nd2).getPosition());
		sf::Vector2f vDist = vTo - vFrom;
		return sqrt(vDist.x*vDist.x + vDist.y*vDist.y);
	}
};