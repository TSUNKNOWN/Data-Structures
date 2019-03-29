// Queue.h
#ifndef _QUEUE_H_
#define _QUEUE_H_
#include <stdexcept>
#include "Node.h"
using namespace std;

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
class LinkedQueue : public QueueInterface<ItemType>
{
private:
	Node<ItemType>* frontPtr;
	Node<ItemType>* backPtr;
public:
	LinkedQueue();
	LinkedQueue(const LinkedQueue<ItemType>& aQueue);
	~LinkedQueue();
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	ItemType peekFront() const;
};

template<class ItemType>
class ArrayQueue : public QueueInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 50;
	ItemType* items;
	int front;
	int back;
	int itemCount;
	int maxItems;
public:
	ArrayQueue();
	ArrayQueue(const ArrayQueue<ItemType>& aQueue);
	~ArrayQueue();
	bool isEmpty() const;
	bool enqueue(const ItemType& newEntry);
	bool dequeue();
	ItemType peekFront() const;
};

//=================================================================================================
// LinkedQueue
//=================================================================================================
template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue() : frontPtr(nullptr), backPtr(nullptr)
{
}

template<class ItemType>
LinkedQueue<ItemType>::LinkedQueue(const LinkedQueue<ItemType>& aQueue)
{
	Node<ItemType>* origChainPtr = aQueue.frontPtr;
	if (origChainPtr == nullptr)
	{
		frontPtr = nullptr;
		backPtr = nullptr;
	}
	else
	{	// copy first node
		frontPtr = new Node<ItemType>(origChainPtr->item);

		// copy remaining nodes
		backPtr = frontPtr;
		origChainPtr = origChainPtr->next;
		while (origChainPtr != nullptr)
		{
			backPtr->next = new Node<ItemType>(origChainPtr->item);
			backPtr = backPtr->next;
			origChainPtr = origChainPtr->next;
		}

		backPtr->next = nullptr; // Flag end of new chain
	}
}

template<class ItemType>
LinkedQueue<ItemType>::~LinkedQueue()
{
	while (!isEmpty())
		dequeue();
}

template<class ItemType>
bool LinkedQueue<ItemType>::isEmpty() const
{
	return (frontPtr == nullptr);
}

template<class ItemType>
bool LinkedQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);

	if (isEmpty()) // insertion into empty queue
		frontPtr = newNodePtr;
	else // insertion into nonempty queue
		backPtr->next = newNodePtr;

	backPtr = newNodePtr;
	return true;
}

template<class ItemType>
bool LinkedQueue<ItemType>::dequeue()
{
	bool result = false;
	if (!isEmpty())
	{
		Node<ItemType>* nodeToDeletePtr = frontPtr;
		if (frontPtr == backPtr) // A queue with one item
		{
			frontPtr = nullptr;
			backPtr = nullptr;
		}
		else // A queue with multi items
			frontPtr = frontPtr->next;

		nodeToDeletePtr->next = nullptr;
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}
	return result;
}

template<class ItemType>
ItemType LinkedQueue<ItemType>::peekFront() const
{
	if (isEmpty())
		throw logic_error("Precondition Violated Exception: peekFront() called with an empty queue.\n");

	return frontPtr->item;
}

//=================================================================================================
// ArrayQueue
//=================================================================================================
template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue() : front(0), back(DEFAULT_CAPACITY - 1), itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	items = new ItemType[maxItems];
}

template<class ItemType>
ArrayQueue<ItemType>::ArrayQueue(const ArrayQueue<ItemType>& aQueue)
{
	front = aQueue.front;
	back = aQueue.back;
	itemCount = aQueue.itemCount;
	maxItems = aQueue.maxItems;
	items = new ItemType[maxItems];
	if (itemCount != 0) // not empty queue
	{
		if (front > back) // seperate into two parts in array
		{
			for (int i = front; i < maxItems; i++) // the back part
				items[i] = aQueue.items[i];
			for (int i = 0; i <= back; i++) // the front part
				items[i] = aQueue.items[i];
		}
		else // only one part in array
		{
			for (int i = front; i <= back; i++)
				items[i] = aQueue.items[i];
		}
	}
}

template<class ItemType>
ArrayQueue<ItemType>::~ArrayQueue()
{
	delete[] items;
}

template<class ItemType>
bool ArrayQueue<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
bool ArrayQueue<ItemType>::enqueue(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (!hasRoomToAdd)
	{
		ItemType* oldArray = items;
		items = new ItemType[2 * maxItems];
		if (front > back) // seperate into two parts in array
		{
			int i = 0;
			for (int j = front; j < maxItems; i++, j++) // the back part
				items[i] = oldArray[j];
			for (int j = 0; j <= back; i++, j++) // the front part
				items[i] = oldArray[j];
			
			front = 0;
			back = maxItems - 1;
		}
		else // front = 0, back = maxItems - 1
		{
			for (int i = 0; i < maxItems; i++)
				items[i] = oldArray[i];
		}
		maxItems *= 2;
	}
	back = (back + 1) % maxItems;
	items[back] = newEntry;
	itemCount++;

	return true;
}

template<class ItemType>
bool ArrayQueue<ItemType>::dequeue()
{
	bool result = false;
	if (!isEmpty())
	{
		front = (front + 1) % maxItems;
		itemCount--;
		result = true;
	}
	return result;
}

template<class ItemType>
ItemType ArrayQueue<ItemType>::peekFront() const
{
	if (isEmpty())
		throw logic_error("Precondition Violated Exception: peekFront() called with an empty queue.\n");

	return items[front];
}
#endif // !_QUEUE_H_
