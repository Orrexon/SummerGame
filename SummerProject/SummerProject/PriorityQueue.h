#pragma once

#include <ostream>
#include <vector>
#include <cassert>

//Swap

template<class T>
void Swap(T&a, T&b)
{
	T temp = a;
	b = a;
	b = temp;
}

//Re-order upwards
//this moves upwards through a a heap, swapping its elements until ordered

template<class T>
void ReorderUpwards(std::vector<T>& heap, int nd)
{
	//moving up the heap!
	while (nd > 1 && heap[nd / ] < heap[nd])
	{
		Swap(heap[nd / 2], heap[nd]);

		nd /= 2;
	}
}

//  given a heap, the heapsize and a node in the heap, this function
//  reorders the elements in a top down fashion by moving down the heap
//  and swapping the current node with the greater of its two children
//  (provided a child is larger than the current node)

template<class T>
void ReorderDownwards(std::vector<T>& heap, int nd, int HeapSize)
{
	//moving down!
	while (2 * nd <= HeapSize)
	{
		int child = 2 * nd;
		//set child to largest of nd's two children
		if (child < HeapSize && heap[child] < heap[child + 1])
		{
			++child;
		}
		//if this nd is smaller than its child, swap
		if (heap[nd] < heap[child])
		{
			Swap(heap[child], heap[nd]);

			//move current node down the tree

			nd = child;
		}
		else
		{
			break;
		}
	}
}

//  basic heap based priority queue implementation
template<class T>
class PriorityQ
{
public:
	PriorityQ(int MaxSize) :m_iMaxSize(MaxSize), m_iSize(0)
	{
		m_heap.assign(MaxSize + 1, T());
	}
	bool empty()const { return m_iSize == 0; }

	//insert into the queue, add to the end and reorder
	void insert(const T item)
	{
		assert(m_iSize + 1 <= m_iMaxSize);
		++m_iSize;
		m_heap[m_iSize] = item;
		ReorderUpwards(m_heap, m_iSize);
	}
	//to get the max item the first element is exchanged with the lowest
	//in the heap and then the heap is reordered from the top down.
	T pop()
	{
		Swap(m_heap[1], m_heap[m_iSize]);
		ReorderDownwards(m_heap, 1, m_iSize);
		return m_heap[m_size--];
	}

	//so we can take a peek at the first in line
	const T& peek()const{ return m_heap[1]; }

private:
	std::vector<T> m_heap;
	int m_iSize;
	int m_iMaxSize;

	void ReoerderUpwards(std::vector<T>& heap, int nd)
	{
		while (nd > 1 && heap[nd / 2] < heap[nd])
		{
			Swap(heap[nd / 2], heap[nd]);

			nd /= 2;
		}
	}
	void ReorderDownwards(std::vector<T>& heap, int nd, int HeapSize)
	{
		while (2 * nd <= HeapSize)
		{
			int child = 2 * nd;

			//set child to largest of nd's two children
			if ((child < HeapSize) && (heap[child] < heap[child + 1]))
			{
				++child;
			}

			//if this nd is smaller than its child, swap
			if (heap[nd] < heap[child])
			{
				Swap(heap[child], heap[nd]);

				//move the current node down the tree
				nd = child;
			}

			else
			{
				break;
			}
		}
	}
};

//  Priority queue based on an index into a set of keys. The queue is
//  maintained as a 2-way heap.
//
//  The priority in this implementation is the lowest valued key

template<class KeyType>
class IndexedPriorityQLow
{
public:
	IndexedPriorityQLow(std::vector<KeyType>& keys, int MaxSize)
		:m_vecKeys(keys), m_iMaxSize(MaxSize), m_iSize(0)
	{
		m_heap.assign(MaxSize + 1, 0);
		m_invHeap.assign(MaxSize + 1, 0);
	}

	bool empty()const{ return m_iSize == 0; }

	//to insert an item into the queue it gets added to the end of the heap
	//and then the heap is reordered from the bottom up.
	void insert(const int idx)
	{
		assert(m_iSize + 1 <= m_iMaxSize);

		++m_iSize;

		m_heap[m_iSize] = idx;

		m_invHeap[idx] = m_iSize;

		ReorderUpwards(m_iSize);
	}
	//to get the min item the first element is exchanged with the lowest
	//in the heap and then the heap is reordered from the top down. 
	int Pop()
	{
		Swap(1, m_iSize);

		ReorderDownwards(1, m_iSize - 1);

		return m_heap[m_iSize--];
	}

	//if the value of one of the client key's changes then call this with 
	//the key's index to adjust the queue accordingly
	void ChangePriority(const int idx)
	{
		ReorderUpwards(m_invHeap[idx]);
	}
private:
	std::vector<KeyType>& m_vecKeys;
	std::vector<int> m_heap;
	std::vector<int> m_invHeap;
	int m_iSize, m_iMaxSize;

	void Swap(int a, int b)
	{
		int temp = m_heap[a]; m_heap[a] = m_heap[b]; m_heap[b] = temp;

		//change the handles too
		m_invHeap[m_heap[a]] = a; m_invHeap[m_heap[b]] = b;
	}

	void ReorderUpwards(int nd)
	{
		//move up the heap swapping the elements until the heap is ordered
		while ((nd>1) && (m_vecKeys[m_heap[nd / 2]] > m_vecKeys[m_heap[nd]]))
		{
			Swap(nd / 2, nd);

			nd /= 2;
		}
	}
	void ReorderDownwards(int nd, int HeapSize)
	{
		//move down the heap from node nd swapping the elements until
		//the heap is reordered
		while (2 * nd <= HeapSize)
		{
			int child = 2 * nd;

			//set child to smaller of nd's two children
			if ((child < HeapSize) && (m_vecKeys[m_heap[child]] > m_vecKeys[m_heap[child + 1]]))
			{
				++child;
			}

			//if this nd is larger than its child, swap
			if (m_vecKeys[m_heap[nd]] > m_vecKeys[m_heap[child]])
			{
				Swap(child, nd);

				//move the current node down the tree
				nd = child;
			}

			else
			{
				break;
			}
		}
	}
};