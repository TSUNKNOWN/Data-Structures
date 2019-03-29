// ListQueue.h
#ifndef _LIST_QUEUE_H_
#define _LIST_QUEUE_H_
#include "List.h"

template<class ItemType>
class QueueInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool enqueue(const ItemType& newEntry) = 0;
	virtual bool dequeue() = 0;
	virtual ItemType peekFront() const = 0;
};

template<class ItemType>
class ListQueue : public QueueInterface<ItemType>
{
private:
	LinkedList<ItemType>* listPtr;
public:
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	ItemType peekFront() const;
};

//=================================================================================================
// ListQueue
//=================================================================================================
template<class ItemType>
bool ListQueue<ItemType>::isEmpty() const
{
	return listPtr->isEmpty();
}

template<class ItemType>
bool ListQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	return listPtr->insert(listPtr->getLength + 1, newEntry);
}

template<class ItemType>
bool ListQueue<ItemType>::dequeue()
{
	return listPtr->remove(1);
}

template<class ItemType>
ItemType ListQueue<ItemType>::peekFront() const
{
	if(isEmpty())
		throw logic_error("Precondition Violated Exception: peekFront() called with an empty queue.\n");
	return listPtr->getEntry(1);
}

#endif // !_LIST_QUEUE_H_
