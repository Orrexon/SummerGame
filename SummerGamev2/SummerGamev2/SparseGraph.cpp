//SparceGraph.cpp

//#include "SparseGraph.h"

//template <class node_type, class edge_type>
//const node_type& SparseGraph<node_type, edge_type>::getNode(int index)const
//{
//	assert((index < static_cast<int>(m_nodes.size()) &&
//		index >= 0) &&
//		"<SparseGraph::GetNode>: invalid index");
//	return m_nodes[index];
//}
//
//template <class node_type, class edge_type>
//node_type& SparseGraph<node_type, edge_type>::getNode(int index)
//{
//	assert((index < static_cast<int>(m_nodes.size()) &&
//		index >= 0) &&
//		"<SparseGraph::GetNode>: invalid index");
//	return m_nodes[index];
//}
//
//template <class node_type, class edge_type>
//const edge_type& SparseGraph<node_type, edge_type>::getEdge(int from, int to)const
//{
//	assert((from < m_nodes.size()) &&
//		from >= 0 &&
//		m_nodes[from].Index() != -1 &&
//		"<SparseGraph::getEdge> invalid 'from' index");
//
//	assert((to < m_nodes.size()) &&
//		to >= 0 &&
//		m_nodes[to].Index() != -1 &&
//		"<SparseGraph::getEdge> invalid 'to' index");
//
//	for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
//		curEdge != m_Edges[from].end();
//		++curEdge)
//	{
//		if (curEdge->To() == to) return *curEdge;
//	}
//	assert(0 && "<SparseGraph::getEdge>: edge does not exist");
//}
//
//template <class node_type, class edge_type>
//edge_type& SparseGraph<node_type, edge_type>::getEdge(int from, int to)
//{
//	assert((from < m_nodes.size()) &&
//		from >= 0 &&
//		m_nodes[from].Index() != -1 &&
//		"<SparseGraph::getEdge> invalid 'from' index");
//
//	assert((to < m_nodes.size()) &&
//		to >= 0 &&
//		m_nodes[to].Index() != -1 &&
//		"<SparseGraph::getEdge> invalid 'to' index");
//
//	for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
//		curEdge != m_Edges[from].end();
//		++curEdge)
//	{
//		if (curEdge->To() == to) return *curEdge;
//	}
//	assert(0 && "<SparseGraph::getEdge>: edge does not exist");
//}
//
//template <class node_type, class edge_type>
//int SparseGraph<node_type, edge_type>::getNextFreeNodeIndex()const
//{
//	return m_iNextNodeIndex;
//}
//
//template <class node_type, class edge_type>
//int SparseGraph<node_type, edge_type>::addNode(node_type node)
//{
//	if (node.Index() < static_cast<int>(m_Nodes.size()))
//	{
//		//make sure the client is not trying to add a node with the same ID as
//		//a currently active node
//		assert(m_Nodes[node.Index()].Index() == -1 &&
//			"<SparseGraph::AddNode>: Attempting to add a node with a duplicate ID");
//
//		m_Nodes[node.Index()] = node;
//
//		return m_iNextNodeIndex;
//	}
//
//	else
//	{
//		//make sure the new node has been indexed correctly
//		assert(node.Index() == m_iNextNodeIndex && "<SparseGraph::AddNode>:invalid index");
//
//		m_Nodes.push_back(node);
//		m_Edges.push_back(EdgeList());
//
//		return m_iNextNodeIndex++;
//	}
//}
//
//template <class node_type, class edge_type>
//void SparseGraph<node_type, edge_type>::removeNode(int node)
//{
//	assert(node < static_cast(m_nodes.size()) && "<SparseGraph::removeNode>: invalid node index");
//
//	m_nodes[node].setIndex(-1);
//
//	if (!m_bDigraph)
//	{
//		for (EdgeList::iterator curEdge = m_Edges[node].begin();
//			curEdge != m_Edges[node].end();
//			++curEdge)
//		{
//			for (EdgeList::iterator curE = m_Edges[curEdge->To()].begin();
//				curE != m_Edges[curEdge->To()].end();
//				++curE)
//			{
//				if (curE->To() == node)
//				{
//					curE = m_Edges[curEdge->To()].erase(curE);
//					break;
//				}
//			}
//		}
//		//clear the edges
//		m_Edges[node].clear();
//	}
//	else
//	{
//		cullInvalidEdges();
//	}
//}
//
//template <class node_type, class edge_type>
//void SparseGraph<node_type, edge_type>::addEdge(EdgeType edge)
//{
//	//make sure the from and to nodes exist
//	assert(edge.From() < m_iNextNodeIndex && edge.To() < m_iNextNodeIndex &&
//		"<SparseGraph::addEdge>: invalid node index");
//	//make sure they're active
//	if (m_nodes[edge.To()].Index() != -1 &&
//		m_nodes[edge.From()].Index() != -1)
//	{
//		//make sure it's unique and add it
//		if (UniqueEdge(edge.From(), edge.To()))
//		{
//			m_Edges[edge.From()].push_back(edge);
//		}
//
//		//if the graph is undirected add connection in the opposite dir
//		if (!m_bDigraph)
//		{
//			//unique?
//			if (UniqueEdge(edge.To(), edge.From()))
//			{
//				EdgeType NewEdge = edge;
//
//				NewEdge.setTo(edge.From());
//				NewEdge.setFrom(edge.To());
//
//				m_Edges[edge.To()].push_back(NewEdge);
//			}
//		}
//	}
//}
//
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::UniqueEdge(int from, int to)const
//{
//	for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
//		curEdge != m_Edges[from].end();
//		++curEdge)
//	{
//		if (curEdge->To() == to)
//		{
//			return false;
//		}
//	}
//
//	return true;
//}
//
//
//template <class node_type, class edge_type>
//void SparseGraph<node_type, edge_type>::removeEdge(int from, int to)
//{
//	assert((from < static_cast<int>(m_Nodes.size())) && (to < static_cast<int>(m_Nodes.size())) &&
//		"<SparseGraph::RemoveEdge>:invalid node index");
//
//	EdgeList::iterator curEdge;
//
//	if (!m_bDigraph)
//	{
//		for (curEdge = m_Edges[to].begin();
//			curEdge != m_Edges[to].end();
//			++curEdge)
//		{
//			if (curEdge->To() == from){ curEdge = m_Edges[to].erase(curEdge); break; }
//		}
//	}
//
//	for (curEdge = m_Edges[from].begin();
//		curEdge != m_Edges[from].end();
//		++curEdge)
//	{
//		if (curEdge->To() == to){ curEdge = m_Edges[from].erase(curEdge); break; }
//	}
//}
//
//template <class node_type, class edge_type>
//void SparseGraph<node_type, edge_type>::setEdgeCost(int from, int to, double cost)
//{
//	//make sure the nodes given are valid
//	assert((from < static_cast<int>(m_Nodes.size())) && (to < static_cast<int>(m_Nodes.size())) &&
//		"<SparseGraph::SetEdgeCost>: invalid index");
//
//	for (EdgeList::iterator curEdge = m_Edges[from].begin();
//		curEdge != m_Edges[from].end();
//		++curEdge)
//	{
//		if (curEdge->To() == to)
//		{
//			curEdge->setCost(cost);
//			break;
//		}
//	}
//}
//
//template <class node_type, class edge_type>
//int SparseGraph<node_type, edge_type>::numNodes()const
//{
//	return m_nodes.size();
//}
//
//template <class node_type, class edge_type>
//int SparseGraph<node_type, edge_type>::numActiveNodes()const
//{
//	int count = 0;
//
//	for (size_t i = 0; i < m_nodes.size(); ++i)
//	{
//		if (m_nodes[i].Index() != -1) ++count;
//	}
//	return count;
//}
//
//template <class node_type, class edge_type>
//int SparseGraph<node_type, edge_type>::numEdges()const
//{
//	int tot = 0;
//
//	for (EdgeListVector::const_iterator curEdge = m_Edges.begin();
//		curEdge != m_Edges.end();
//		++curEdge)
//	{
//		tot += curEdge->size();
//	}
//	return tot;
//}
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::isDigraph()const { return m_bDigraph; }
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::isEmpty()const { return m_nodes.empty(); }
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::isNodePresent(int nd)const
//{
//	if (nd >= (int)m_nodes.size() || m_nodes.Index() == -1)
//	{
//		return false;
//	}
//	else return true;
//}
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::isEdgePresent(int from, int to)const
//{
//	//This is really wierd!!!!!!!!!!!!!!!!!!
//	if (isNodePresent(from) && isNodePresent(from))
//	{
//		for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
//			curEdge != m_Edges[from].end();
//			++curEdge)
//		{
//			if (curEdge->To() == to)
//			{
//				return true;
//			}
//		}
//		return false;
//	}
//	else return false;
//}
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::save(const char* filename)const
//{
//	//open the file and make sure it's valid
//	std::ofstream out(filename);
//
//	if (!out)
//	{
//		throw std::runtime_error("Cannot open file: " + std::string(filename));
//		return false;
//	}
//
//	return save(out);
//}
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::save(std::ofstream& stream) const
//{
//	//save the number of nodes
//	stream << m_Nodes.size() << std::endl;
//
//	//iterate through the graph nodes and save them
//	NodeVector::const_iterator curNode = m_Nodes.begin();
//	for (curNode; curNode != m_Nodes.end(); ++curNode)
//	{
//		stream << *curNode;
//	}
//
//	//save the number of edges
//	stream << NumEdges() << std::endl;
//
//
//	//iterate through the edges and save them
//	for (unsigned int nodeIdx = 0; nodeIdx < m_Nodes.size(); ++nodeIdx)
//	{
//		for (EdgeList::const_iterator curEdge = m_Edges[nodeIdx].begin();
//			curEdge != m_Edges[nodeIdx].end(); ++curEdge)
//		{
//			stream << *curEdge;
//		}
//	}
//
//	return true;
//}
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::load(const char* fileName)const
//{
//	//open file and make sure it's valid
//	std::ifstream in(fileName);
//
//	if (!in)
//	{
//		throw std::runtime_error("Cannot open file: " + std::string(fileName));
//		return false;
//	}
//
//	return load(in);
//}
//
//template <class node_type, class edge_type>
//bool SparseGraph<node_type, edge_type>::load(std::ifstream& stream)const
//{
//	clearGraph();
//
//	//get the number of nodes and read them in
//	int NumNodes, NumEdges;
//
//	stream >> NumNodes;
//
//	for (int n = 0; n<NumNodes; ++n)
//	{
//		NodeType NewNode(stream);
//
//		//when editing graphs it's possible to end up with a situation where some
//		//of the nodes have been invalidated (their id's set to invalid_node_index). Therefore
//		//when a node of index invalid_node_index is encountered, it must still be added.
//		if (NewNode.Index() != invalid_node_index)
//		{
//			addNode(NewNode);
//		}
//		else
//		{
//			m_nodes.push_back(NewNode);
//
//			//make sure an edgelist is added for each node
//			m_Edges.push_back(EdgeList());
//
//			++m_iNextNodeIndex;
//		}
//	}
//
//	//now add the edges
//	stream >> NumEdges;
//	for (int e = 0; e<NumEdges; ++e)
//	{
//		EdgeType NextEdge(stream);
//
//		addEdge(NextEdge);
//	}
//
//	return true;
//}
//
//template <class node_type, class edge_type>
//void SparseGraph<node_type, edge_type>::clearGraph()
//{
//	m_iNextNodeIndex = 0;
//	m_nodes.clear();
//	m_Edges.clear();
//}
//
//template <class node_type, class edge_type>
//void SparseGraph<node_type, edge_type>::removeEdges()
//{
//	for (EdgeListVector::iterator it = m_Edges.begin(); it != m_Edges.end(); ++it)
//	{
//		it->clear();
//	}
//}
//
//template <class node_type, class edge_type>
//void SparseGraph<node_type, edge_type>::cullInvalidEdges()
//{
//	for (EdgeListVector::iterator curEdgeList = m_Edges.begin(); curEdgeList != m_Edges.end(); ++curEdgeList)
//	{
//		for (EdgeList::iterator curEdge = (*curEdgeList).begin(); curEdge != (*curEdgeList).end(); ++curEdge)
//		{
//			if (m_Nodes[curEdge->To()].Index() == -1 ||
//				m_Nodes[curEdge->From()].Index() == -1)
//			{
//				curEdge = (*curEdgeList).erase(curEdge);
//			}
//		}
//	}
//}