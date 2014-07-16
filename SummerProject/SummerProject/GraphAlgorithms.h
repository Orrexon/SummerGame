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
		sf::Vector2f vFrom = G.getNode(nd2).getPosition();
		sf::Vector2f vTo = G.getNode(nd1).getPosition();
		sf::Vector2f vDist = vTo - vFrom;
		return sqrt(vDist.x*vDist.x + vDist.y*vDist.y);
	}
};

//Graph Search DFS
template<class graph_type>
bool Graph_SearchDFS<graph_type>::Search()
{
	//create an std::stack of edges
	sdt::stack<const Edge*> stack;

	//create a dummy edge and put on the stack
	stack.push(&Dummy);

	//while there are edges on the stack keep searching
	while (!stack.empty())
	{
		//grab the next edge
		const Edge* Next = stack.top();

		//remove the edge from the stack
		stack.pop();

		//make a note to the parent of the node this edge points to
		m_Route[Next->To()] = Next->From();

		//put it on the tree, make sure it's not the dummy
		//(Only for drawing the edges)
		if (Next != &Dummy)
		{
			m_SpanningTree.push_back(Next);
		}

		//mark it visited
		m_Visited[Next->To()] = visited;

		//if target is found return true
		if (Next->To() == m_iTarget)
		{
			return true;
		}

		//Push the edges leading from the node this edge points to onto
		//the stack, if the edge does not point to a visited node.
		graph_type::ConstEdgeIterator ConstEdgeItr(m_Graph, Next->To());

		for (const Edge* pE = ConstEdgeItr.begin();
			!ConsEdgeItr.end();
			pE = ConstEdgeItr.next())
		{
			if (m_Visited[pE->To()] == unvisited)
			{
				stack.push(pE);
			}
		}
	}

	//no path to target
	return false;
}

template <class graph_type>
std::list<int> Graph_SearchDFS<graph_type>::getPathToTarget()const
{
	std::list<int> path;

	//just return an empty path if no path to target found or if
	//no target has been specified
	if (!m_bFound || m_iTarget<0) return path;

	int nd = m_iTarget;

	path.push_front(nd);

	while (nd != m_iSource)
	{
		nd = m_Route[nd];

		path.push_front(nd);
	}

	return path;
}


//Graph Search BFS
template <class graph_type>
bool Graph_SearchBFS<graph_type>::Search()
{
	//create an std queue of edges
	std::queue<const Edge*> Q;

	const Edge Dummy(m_iSource, m_iSource, 0);

	Q.push(&Dummy);

	//mark the node as visited
	m_Visited[m_iSource] = visited;

	while (!Q.empty())
	{
		const Edge* Next = Q.front();

		Q.pop();

		//mark the parent of this node
		m_Route[Next->To()] = Next->From();

		if (Next != &Dummy)
		{
			m_SpanningTree.push_back(Next);
		}

		if (Next->To() == m_iTarget)
		{
			return true;
		}
		//Push the edges leading from the node at the end of this edge
		//onto the queue
		graph_type::ConstEdgeIterator ConstEdgeItr(m_Graph, Next->To());

		for (const Edge* pE = ConstEdgeItr.begin();
			!ConstEdgeItr.end();
			pE = ConstEdgeItr.next())
		{
			if (m_Visited[pE->To()] == unvisited)
			{
				Q.push(pE);

				m_Visited[pE->To()] = visited;
			}
		}
	}
	return false;
}

template <class graph_type>
std::list<int> Graph_SearchBFS<graph_type>::getPathToTarget()const
{
	std::list<int> path;

	//just return an empty path if no path to target found or if
	//no target has been specified
	if (!m_bFound || m_iTarget<0) return path;

	int nd = m_iTarget;

	path.push_front(nd);

	while (nd != m_iSource)
	{
		nd = m_Route[nd];

		path.push_front(nd);
	}

	return path;
}

//Dijkstra
template <class graph_type>
void Graph_SearchDijkstra<graph_type>::Search()
{
	//create an indexed priority queue that sorts smallest to largest
	//(front to back).Note that the maximum number of elements the iPQ
	//may contain is N. This is because no node can be represented on the 
	//queue more than once.
	IndexedPriorityQLow<double> pq(m_CostToThisNode, m_Graph.NumNodes());

	//put the source node on the queue
	pq.insert(m_iSource);

	while (!pq.empty())
	{
		int NextClosestNode = pq.Pop();

		m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];

		//exit if the target has been found
		if (NextClosestNode == m_iTarget) return;

		//Relaxing the edges
		graph_type::ConstEdgeIterator ConstEdgeItr(m_Graph, NextClosestNode);

		//for each edge connected to the next closest node
		for (const Edge* pE = ConstEdgeItr.begin();
			!ConstEdgeItr.end();
			pE = ConstEdgeItr.next())
		{
			//the total cost to the node this edge points to is the cost to the
			//current node plus the cost of the edge connecting them.
			double NewCost = m_CostToThisNode[NextClosestNode] + pE->Cost();

			//if this edge has never been on the frontier make a note of the cost
			//to get to the node it points to, then add the edge to the frontier
			//and the destination node to the PQ.
			if (m_SearchFrontier[pE->To()] == 0)
			{
				m_CostToThisNode[pE->To()] = NewCost;
				pq.insert(pE->To());
				m_SearchFrontier[pE->To()] = pE;
			}
			//else test to see if the cost to reach the destination node via the
			//current node is cheaper than the cheapest cost found so far. If
			//this path is cheaper, we assign the new cost to the destination
			//node, update its entry in the PQ to reflect the change and add the
			//edge to the frontier
			else if (NewCost < m_CostToThisNode[pE->To()] &&
				m_ShortestPathTree[pE->To()] == 0)
			{
				m_CostToThisNode[pE->To()] = NewCost;

				//because the cost is less than it was previously, the PQ must be
				//re-sorted to account for this.
				pq.ChangePriority(pE->To());

				m_SearchFrontier[pE->To()] = pE;
			}
		}
	}
}

template <class graph_type>
std::list<int> Graph_SearchDijkstra<graph_type>::getPathToTarget()const
{
	std::list<int> path;

	//just return an empty path if no target or no path found
	if (m_iTarget < 0)  return path;

	int nd = m_iTarget;

	path.push_front(nd);

	while ((nd != m_iSource) && (m_ShortestPathTree[nd] != 0))
	{
		nd = m_ShortestPathTree[nd]->From();

		path.push_front(nd);
	}

	return path;
}


//Graph Search AStar
template <class graph_type, class heuristic>
void Graph_SearchAStar<graph_type, heuristic>::Search()
{
	//create an indexed priority queue of nodes. The nodes with the
	//lowest overall F cost (G+H) are positioned at the front.
	IndexedPriorityQLow<double> pq(m_FCosts, m_Graph.numNodes());

	pq.insert(m_iSource);

	while (!pq.empty())
	{
		int NextClosestNode = pq.Pop();

		m_ShortestPathTree[NextClosestNode] = m_SearchFrontier[NextClosestNode];

		if (NextClosestNode == m_iTarget) return;

		//test all the edges attached to this node
		graph_type::ConstEdgeIterator ConstEdgeItr(m_Graph, NextClosestNode);

		for (const Edge* pE = ConstEdgeItr.begin();
			!ConstEdgeItr.end();
			pE = ConstEdgeItr.next())
		{
			//calculate the heuristic cost from this node to the target (H)
			double HCost = heuristic::Calculate(m_Graph, m_iTarget, pE->To());

			//calculate the 'real' cost to this node from the source
			double GCost = m_GCosts[NextClosestNode] + pE->Cost();

			//if the node has not been added to the frontier, add it and update
			//the G and F costs
			if (m_SearchFrontier[pE->To()] == nullptr)
			{
				m_FCosts[pE->To()] = GCost + HCost;
				m_GCosts[pE->To()] = GCost;

				pq.insert(pE->To());

				m_SearchFrontier[pE->To()] = pE;
			}

			//if this node is already on the frontier but the cost to get here
			//is cheaper than has been found previously, update the node
			//costs and frontier accordingly.
			else if ((GCost < m_GCosts[pE->To()]) && (m_ShortestPathTree[pE->To()] == nullptr))
			{
				m_FCosts[pE->To()] = GCost + HCost;
				m_GCosts[pE->To()] = GCost;

				pq.ChangePriority(pE->To());

				m_SearchFrontier[pE->To()] = pE;
			}
		}
	}
}

template <class graph_type, class heuristic>
std::list<int> Graph_SearchAStar<graph_type, heuristic>::getPathToTarget()const
{
	std::list<int> path;

	//just return an empty path if no target or no path found
	if (m_iTarget < 0)  return path;

	int nd = m_iTarget;

	path.push_front(nd);

	while ((nd != m_iSource) && (m_ShortestPathTree[nd] != 0))
	{
		nd = m_ShortestPathTree[nd]->From();

		path.push_front(nd);
	}

	return path;
}