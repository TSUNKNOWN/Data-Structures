// SL_PriorityQueue2.h
// The BIGGER entry has the HIGHER priority in this SL_PriorityQueue
// ex: High <====> Low
//      7 > 5 > 3 > 1
//      s > m > f > a
#ifndef _SL_PRIORITY_QUEUE_2_H_
#define _SL_PRIORITY_QUEUE_2_H_
#include "SortedList2.h"

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
class SL_PriorityQueue2 : public PriorityQueueInterface<ItemType>
{
private:
	LinkedSortedList2<ItemType>* slistPtr; // pointer to sorted list PriorityQueue
public:
	SL_PriorityQueue2();
	SL_PriorityQueue2(const SL_PriorityQueue2<ItemType>& aSL_PQ);
	~SL_PriorityQueue2();
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove();
	ItemType peek() const;
};

//=================================================================================================
// SL_PriorityQueue2
//=================================================================================================
template<class ItemType>
SL_PriorityQueue2<ItemType>::SL_PriorityQueue2()
{
	slistPtr = new LinkedSortedList2<ItemType>();
}

template<class ItemType>
SL_PriorityQueue2<ItemType>::SL_PriorityQueue2(const SL_PriorityQueue2<ItemType>& aSL_PQ)
{
	slistPtr = new LinkedSortedList2<ItemType>(*(aSL_PQ.slistPtr));
}

template<class ItemType>
SL_PriorityQueue2<ItemType>::~SL_PriorityQueue2()
{
	delete slistPtr;
}

template<class ItemType>
bool SL_PriorityQueue2<ItemType>::isEmpty() const
{
	return slistPtr->isEmpty();
}

template<class ItemType>
bool SL_PriorityQueue2<ItemType>::add(const ItemType& newEntry)
{
	slistPtr->insertSorted(newEntry);
	return true;
}

template<class ItemType>
bool SL_PriorityQueue2<ItemType>::remove()
{
	return slistPtr->remove(1); // the biggest one
								// the highest priority
}

template<class ItemType>
ItemType SL_PriorityQueue2<ItemType>::peek() const
{
	return slistPtr->getEntry(1); // the biggest one
								  // the highest priority
}

#endif // !_SL_PRIORITY_QUEUE_2_H_
