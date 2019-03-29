// Heap_PriorityQueue.h
#ifndef _HEAP_PRIORITY_QUEUE_H_
#define _HEAP_PRIORITY_QUEUE_H_
#include <stdexcept>
#include "Heap.h"
using namespace std;

template<class ItemType>
class PriorityQueueInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool add(const ItemType& newEntry) = 0;
	virtual bool remove() = 0;
	virtual ItemType peek() const = 0;
};

template<class ItemType>
class Heap_PriorityQueue
	: public PriorityQueueInterface<ItemType>,
	  private ArrayMaxHeap<ItemType>
{
public:
	Heap_PriorityQueue();
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove();
	ItemType peek() const;
};

//=================================================================================================
// Heap_PriorityQueue
//=================================================================================================
template<class ItemType>
Heap_PriorityQueue<ItemType>::Heap_PriorityQueue()
{
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::isEmpty() const
{
	return ArrayMaxHeap<ItemType>::isEmpty();
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::add(const ItemType& newEntry)
{
	return ArrayMaxHeap<ItemType>::add(newEntry);
}

template<class ItemType>
bool Heap_PriorityQueue<ItemType>::remove()
{
	return ArrayMaxHeap<ItemType>::remove();
}

template<class ItemType>
ItemType Heap_PriorityQueue<ItemType>::peek() const
{
	try {
		return ArrayMaxHeap<ItemType>::peekTop();
	}
	catch (logic_error e) {
		throw logic_error("Precondition Violated Exception: peek() called with an empty priority queue.\n");
	}

}
#endif // !_HEAP_PRIORITY_QUEUE_H_
