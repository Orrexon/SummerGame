//GraphAlgorithms.cpp

#include "GraphAlgorithms.h"



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
std::list<int> Graph_SearchBFS<graph_type>::GetPathToTarget()const
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
	IndexedPriorityQLow<double> pq(m_FCosts, m_Graph.numNudes());

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
			double HCost = heuristic::Calculate(m_graph, m_iTarget, pE->To());
			
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