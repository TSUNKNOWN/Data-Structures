// SL_PriorityQueue.h
// The SMALLER entry has the HIGHER priority in this SL_PriorityQueue
// ex: High <====> Low
//      1 < 3 < 5 < 7
//	    a < f < m < s
#ifndef _SL_PRIORITY_QUEUE_H_
#define _SL_PRIORITY_QUEUE_H_
#include "SortedList.h"

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
class SL_PriorityQueue : public PriorityQueueInterface<ItemType>
{
private:
	LinkedSortedList<ItemType>* slistPtr; // pointer to sorted list PriorityQueue
public:
	SL_PriorityQueue();
	SL_PriorityQueue(const SL_PriorityQueue<ItemType>& aSL_PQ);
	~SL_PriorityQueue();
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove();
	ItemType peek() const;
};

//=================================================================================================
// SL_PriorityQueue
//=================================================================================================
template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue()
{
	slistPtr = new LinkedSortedList<ItemType>();
}

template<class ItemType>
SL_PriorityQueue<ItemType>::SL_PriorityQueue(const SL_PriorityQueue<ItemType>& aSL_PQ)
{
	slistPtr = new LinkedSortedList<ItemType>(*(aSL_PQ.slistPtr));
}

template<class ItemType>
SL_PriorityQueue<ItemType>::~SL_PriorityQueue()
{
	delete slistPtr;
}

template<class ItemType>
bool SL_PriorityQueue<ItemType>::isEmpty() const
{
	return slistPtr->isEmpty();
}

template<class ItemType>
bool SL_PriorityQueue<ItemType>::add(const ItemType& newEntry)
{
	slistPtr->insertSorted(newEntry);
	return true;
}

template<class ItemType>
bool SL_PriorityQueue<ItemType>::remove()
{
	return slistPtr->remove(1); // the smallest one
								// the highest priority
}

template<class ItemType>
ItemType SL_PriorityQueue<ItemType>::peek() const
{
	return slistPtr->getEntry(1); // the smallest one
								  // the highest priority
}
#endif // !_SL_PRIORITY_QUEUE_H_
