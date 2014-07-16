//SparseGraph.h
#pragma once

#include <vector>
#include <list>
#include <assert.h>

template<class node_type, class edge_type>
class SparseGraph
{
public:
	//Typedefs :D to give easy access to the node- and edgetypes, regardless of class names

	typedef node_type NodeType;
	typedef edge_type EdgeType;
	//more typedefs.
	//
	typedef std::vector<node_type>	NodeVector;
	typedef std::list<edge_type>	EdgeList;
	typedef std::vector<EdgeList>	EdgeListVector;
public:
	SparseGraph(bool digraph) :m_bDigraph(digraph), m_iNextNodeIndex(0){}

	const NodeType& getNode(int index)const;
	NodeType& getNode(int index);

	const EdgeType& getEdge(int from, int to)const;
	EdgeType& getEdge(int from, int to);

	int getNextFreeNodeIndex()const;

	//adds a new node and returns its index
	int addNode(NodeType node);

	//removes a node by setting its index to invalid: -1
	void removeNode(int node);

	void addEdge(EdgeType edge);
	void removeEdge(int from, int to);

	bool UniqueEdge(int from, int to) const;

	void setEdgeCost(int from, int to, double cost);

	int numNodes()const;
	int numActiveNodes()const;

	int numEdges()const;

	bool isDigraph() const;

	bool isEmpty()const;

	//returns true if the node with the given index is present
	bool isNodePresent(int index)const;
	bool isEdgePresent(int from, int to)const;

	//save or load graphs
	bool save(const char* fileName)const;
	bool save(std::ofstream& stream)const;
	bool load(const char* fileName)const;
	bool load(std::ifstream& stream)const;

	//clears the graph 
	void clearGraph();

	void removeEdges();

	void cullInvalidEdges();

private:
	//the graph's nodes
	NodeVector m_nodes;

	//a vector of adjacency edge lists. (each node index keys 
	//into the list of edges associated with that node)
	EdgeListVector m_Edges;

	//Is the graph directed or not
	bool m_bDigraph;

	//index of the next node to be added
	int m_iNextNodeIndex;
public:
	//iterators.
	//I decided to have the iterators' declarations here as well because there 
	//would be so many files had I declared them outside. kept the Author's 
	//design in this case --- [insert source here] 
	class EdgeIterator
	{
	public:
		EdgeIterator(SparseGraph<node_type, edge_type>& graph,
			int node) : G(graph),
			NodeIndex(node)
		{
			//no need to check for invalid index since in case a node is invalid there will be no associated edges

			curEdge = G.m_edges[NodeIndex].begin();
		}

		EdgeType* begin()
		{
			curEdge = G.m_Edges[NodeIndex].begin();
			return &(*curEdge);
		}

		EdgeType* next()
		{
			++curEdge;
			if (end()) return nullptr;

			return &(*curEdge);
		}

		//return true if at end of the edge list
		bool end()
		{
			return (curEdge == G.m_Edges[nodeIndex].end());
		}

	private:
		typename EdgeList::iterator curEdge;

		SparseGraph<node_type, edge_type>& G;

		const int NodeIndex;
	};
	friend class EdgeIterator;
	//const interator class
	class ConstEdgeIterator
	{
	public:
		ConstEdgeIterator(const SparseGraph<node_type, edge_type>& graph,int node) 
			: G(graph),
			NodeIndex(node)
		{
			curEdge = G.m_Edges[NodeIndex].begin();
		}

		const EdgeType* begin()
		{
			curEdge = G.m_Edges[NodeIndex].begin();
			if (end()) return nullptr;

			return &(*curEdge);
		}

		const EdgeType* next()
		{
			++curEdge;
			if (end())
			{
				return nullptr;
			}
			else
			{
				return &(*curEdge);
			}
		}
		bool end()
		{
			return (curEdge == G.m_Edges[NodeIndex].end());
		}
	private:
		typename EdgeList::const_iterator curEdge;

		const SparseGraph<node_type, edge_type>& G;

		const int NodeIndex;
	};
	friend class ConstEdgeIterator;

	//node iterator
	class NodeIterator
	{
	public:
		NodeIterator(SparseGraph<node_type, edge_type> & graph) :G(graph)
		{
			curNode = G.m_nodes.begin();
		}

		node_type* begin()
		{
			curNode = G.m_nodes.begin();

			GetNextValidNode(curNode);

			return &(*curNode);
		}

		node_type* next()
		{
			++curNode;
			if (end()) return nullptr;

			GetNextValidNode(curNode);

			return &(*curNode);

		}

		bool end()
		{
			return curNode == G.m_nodes.end();
		}
	private:
		typename NodeVector::iterator curNode;

		SparseGraph<node_type, edge_type>& G;

		//if a graph node is removed it is not removed from the vector
		//of nodes, that would change the indices of all the nodes with
		//higher index. This method takes a node iterator as a parameter
		//and assigns the next valid element to it.
		void GetNextValidNode(typename NodeVector::iterator& it)
		{
			if (curNode == G.m_nodes.end() || it->Index() != -1) return;
			while (it->Index() == -1)
			{
				++it;
				if (curNode == G.m_nodes.end()) break;
			}
		}
	};

	friend class NodeIterator;

	class ConstNodeIterator
	{
	public:
		ConstNodeIterator(const SparseGraph<node_type, edge_type> &graph) :G(graph)
		{
			curNode = G.m_nodes.begin();
		}

		const node_type* begin()
		{
			curNode = G.m_nodes.begin();

			GetNextValidNode(curNode);

			return &(*curNode);
		}

		const node_type* next()
		{
			++curNode;

			if (end())
			{
				return nullptr;
			}
			else
			{
				GetNextValidNode(curNode);

				return &(*curNode);
			}
		}

		bool end()
		{
			return curNode == G.m_nodes.end();
		}
	private:
		typename NodeVector::const_iterator curNode;

		const SparseGraph<node_type, edge_type>& G;

		void GetNextValidNode(typename NodeVector::const_iterator& it)
		{
			if (curNode == G.m_nodes.end() || it->Index() != -1) return;
			while (it->Index() == -1)
			{
				++it;
				if (curNode == G.m_nodes.end()) break;
			}
		}
	};
	friend class ConstNodeIterator;
};

//Apparently you can only explicitly declare templates in a seperate file, or do some strange include business, so I declare them here.
//feel free to tell me how to do it seperatly...
template <class node_type, class edge_type>
const node_type& SparseGraph<node_type, edge_type>::getNode(int index)const
{
	assert((index < static_cast<int>(m_nodes.size()) &&
		index >= 0) &&
		"<SparseGraph::GetNode>: invalid index");
	return m_nodes[index];
}

template <class node_type, class edge_type>
node_type& SparseGraph<node_type, edge_type>::getNode(int index)
{
	assert((index < static_cast<int>(m_nodes.size()) &&
		index >= 0) &&
		"<SparseGraph::GetNode>: invalid index");
	return m_nodes[index];
}

template <class node_type, class edge_type>
const edge_type& SparseGraph<node_type, edge_type>::getEdge(int from, int to)const
{
	assert((from < m_nodes.size()) &&
		from >= 0 &&
		m_nodes[from].Index() != -1 &&
		"<SparseGraph::getEdge> invalid 'from' index");

	assert((to < m_nodes.size()) &&
		to >= 0 &&
		m_nodes[to].Index() != -1 &&
		"<SparseGraph::getEdge> invalid 'to' index");

	for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
		curEdge != m_Edges[from].end();
		++curEdge)
	{
		if (curEdge->To() == to) return *curEdge;
	}
	assert(0 && "<SparseGraph::getEdge>: edge does not exist");
}

template <class node_type, class edge_type>
edge_type& SparseGraph<node_type, edge_type>::getEdge(int from, int to)
{
	assert((from < m_nodes.size()) &&
		from >= 0 &&
		m_nodes[from].Index() != -1 &&
		"<SparseGraph::getEdge> invalid 'from' index");

	assert((to < m_nodes.size()) &&
		to >= 0 &&
		m_nodes[to].Index() != -1 &&
		"<SparseGraph::getEdge> invalid 'to' index");

	for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
		curEdge != m_Edges[from].end();
		++curEdge)
	{
		if (curEdge->To() == to) return *curEdge;
	}
	assert(0 && "<SparseGraph::getEdge>: edge does not exist");
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::getNextFreeNodeIndex()const
{
	return m_iNextNodeIndex;
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::addNode(node_type node)
{
	if (node.Index() < static_cast<int>(m_nodes.size()))
	{
		//make sure the client is not trying to add a node with the same ID as
		//a currently active node
		assert(m_nodes[node.Index()].Index() == -1 &&
			"<SparseGraph::AddNode>: Attempting to add a node with a duplicate ID");

		m_nodes[node.Index()] = node;

		return m_iNextNodeIndex;
	}

	else
	{
		//make sure the new node has been indexed correctly
		assert(node.Index() == m_iNextNodeIndex && "<SparseGraph::AddNode>:invalid index");

		m_nodes.push_back(node);
		m_Edges.push_back(EdgeList());

		return m_iNextNodeIndex++;
	}
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::removeNode(int node)
{
	assert(node < static_cast<int>(m_nodes.size()) && "<SparseGraph::removeNode>: invalid node index");

	m_nodes[node].setIndex(-1);

	if (!m_bDigraph)
	{
		for (EdgeList::iterator curEdge = m_Edges[node].begin();
			curEdge != m_Edges[node].end();
			++curEdge)
		{
			for (EdgeList::iterator curE = m_Edges[curEdge->To()].begin();
				curE != m_Edges[curEdge->To()].end();
				++curE)
			{
				if (curE->To() == node)
				{
					curE = m_Edges[curEdge->To()].erase(curE);
					break;
				}
			}
		}
		//clear the edges
		m_Edges[node].clear();
	}
	else
	{
		cullInvalidEdges();
	}
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::addEdge(EdgeType edge)
{
	//make sure the from and to nodes exist
	assert(edge.From() < m_iNextNodeIndex && edge.To() < m_iNextNodeIndex &&
		"<SparseGraph::addEdge>: invalid node index");
	//make sure they're active
	if (m_nodes[edge.To()].Index() != -1 &&
		m_nodes[edge.From()].Index() != -1)
	{
		//make sure it's unique and add it
		if (UniqueEdge(edge.From(), edge.To()))
		{
			m_Edges[edge.From()].push_back(edge);
		}

		//if the graph is undirected add connection in the opposite dir
		if (!m_bDigraph)
		{
			//unique?
			if (UniqueEdge(edge.To(), edge.From()))
			{
				EdgeType NewEdge = edge;

				NewEdge.setTo(edge.From());
				NewEdge.setFrom(edge.To());

				m_Edges[edge.To()].push_back(NewEdge);
			}
		}
	}
}


template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::UniqueEdge(int from, int to)const
{
	for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
		curEdge != m_Edges[from].end();
		++curEdge)
	{
		if (curEdge->To() == to)
		{
			return false;
		}
	}

	return true;
}


template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::removeEdge(int from, int to)
{
	assert((from < static_cast<int>(m_Nodes.size())) && (to < static_cast<int>(m_Nodes.size())) &&
		"<SparseGraph::RemoveEdge>:invalid node index");

	EdgeList::iterator curEdge;

	if (!m_bDigraph)
	{
		for (curEdge = m_Edges[to].begin();
			curEdge != m_Edges[to].end();
			++curEdge)
		{
			if (curEdge->To() == from){ curEdge = m_Edges[to].erase(curEdge); break; }
		}
	}

	for (curEdge = m_Edges[from].begin();
		curEdge != m_Edges[from].end();
		++curEdge)
	{
		if (curEdge->To() == to){ curEdge = m_Edges[from].erase(curEdge); break; }
	}
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::setEdgeCost(int from, int to, double cost)
{
	//make sure the nodes given are valid
	assert((from < static_cast<int>(m_Nodes.size())) && (to < static_cast<int>(m_Nodes.size())) &&
		"<SparseGraph::SetEdgeCost>: invalid index");

	for (EdgeList::iterator curEdge = m_Edges[from].begin();
		curEdge != m_Edges[from].end();
		++curEdge)
	{
		if (curEdge->To() == to)
		{
			curEdge->setCost(cost);
			break;
		}
	}
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::numNodes()const
{
	return m_nodes.size();
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::numActiveNodes()const
{
	int count = 0;

	for (size_t i = 0; i < m_nodes.size(); ++i)
	{
		if (m_nodes[i].Index() != -1) ++count;
	}
	return count;
}

template <class node_type, class edge_type>
int SparseGraph<node_type, edge_type>::numEdges()const
{
	int tot = 0;

	for (EdgeListVector::const_iterator curEdge = m_Edges.begin();
		curEdge != m_Edges.end();
		++curEdge)
	{
		tot += curEdge->size();
	}
	return tot;
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isDigraph()const { return m_bDigraph; }

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isEmpty()const { return m_nodes.empty(); }

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isNodePresent(int nd)const
{
	if (nd >= (int)m_nodes.size() || m_nodes.Index() == -1)
	{
		return false;
	}
	else return true;
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::isEdgePresent(int from, int to)const
{
	//This is really wierd!!!!!!!!!!!!!!!!!!
	if (isNodePresent(from) && isNodePresent(from))
	{
		for (EdgeList::const_iterator curEdge = m_Edges[from].begin();
			curEdge != m_Edges[from].end();
			++curEdge)
		{
			if (curEdge->To() == to)
			{
				return true;
			}
		}
		return false;
	}
	else return false;
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::save(const char* filename)const
{
	//open the file and make sure it's valid
	std::ofstream out(filename);

	if (!out)
	{
		throw std::runtime_error("Cannot open file: " + std::string(filename));
		return false;
	}

	return save(out);
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::save(std::ofstream& stream) const
{
	//save the number of nodes
	stream << m_nodes.size() << std::endl;

	//iterate through the graph nodes and save them
	NodeVector::const_iterator curNode = m_nodes.begin();
	for (curNode; curNode != m_nodes.end(); ++curNode)
	{
		stream << *curNode;
	}

	//save the number of edges
	stream << numEdges() << std::endl;


	//iterate through the edges and save them
	for (unsigned int nodeIdx = 0; nodeIdx < m_nodes.size(); ++nodeIdx)
	{
		for (EdgeList::const_iterator curEdge = m_Edges[nodeIdx].begin();
			curEdge != m_Edges[nodeIdx].end(); ++curEdge)
		{
			stream << *curEdge;
		}
	}

	return true;
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::load(const char* fileName)const
{
	//open file and make sure it's valid
	std::ifstream in(fileName);

	if (!in)
	{
		throw std::runtime_error("Cannot open file: " + std::string(fileName));
		return false;
	}

	return load(in);
}

template <class node_type, class edge_type>
bool SparseGraph<node_type, edge_type>::load(std::ifstream& stream)const
{
	clearGraph();

	//get the number of nodes and read them in
	int NumNodes, NumEdges;

	stream >> NumNodes;

	for (int n = 0; n<NumNodes; ++n)
	{
		NodeType NewNode(stream);

		//when editing graphs it's possible to end up with a situation where some
		//of the nodes have been invalidated (their id's set to invalid_node_index). Therefore
		//when a node of index invalid_node_index is encountered, it must still be added.
		if (NewNode.Index() != invalid_node_index)
		{
			addNode(NewNode);
		}
		else
		{
			m_nodes.push_back(NewNode);

			//make sure an edgelist is added for each node
			m_Edges.push_back(EdgeList());

			++m_iNextNodeIndex;
		}
	}

	//now add the edges
	stream >> NumEdges;
	for (int e = 0; e<NumEdges; ++e)
	{
		EdgeType NextEdge(stream);

		addEdge(NextEdge);
	}

	return true;
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::clearGraph()
{
	m_iNextNodeIndex = 0;
	m_nodes.clear();
	m_Edges.clear();
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::removeEdges()
{
	for (EdgeListVector::iterator it = m_Edges.begin(); it != m_Edges.end(); ++it)
	{
		it->clear();
	}
}

template <class node_type, class edge_type>
void SparseGraph<node_type, edge_type>::cullInvalidEdges()
{
	for (EdgeListVector::iterator curEdgeList = m_Edges.begin(); curEdgeList != m_Edges.end(); ++curEdgeList)
	{
		for (EdgeList::iterator curEdge = (*curEdgeList).begin(); curEdge != (*curEdgeList).end(); ++curEdge)
		{
			if (m_nodes[curEdge->To()].Index() == -1 ||
				m_nodes[curEdge->From()].Index() == -1)
			{
				curEdge = (*curEdgeList).erase(curEdge);
			}
		}
	}
}