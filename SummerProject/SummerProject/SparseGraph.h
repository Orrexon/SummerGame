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
	friend class ConstNodeIterator;
};