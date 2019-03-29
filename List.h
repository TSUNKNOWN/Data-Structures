// List.h
#ifndef _LIST_H_
#define _LIST_H_
#include <stdexcept>
#include "Node.h"
using namespace std;

template<class ItemType>
class ListInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getLength() const = 0;
	virtual bool insert(int newPosition, const ItemType& newEntry) = 0;
	virtual bool remove(int position) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry(int position) const = 0;
	virtual void setEntry(int position, const ItemType& newEntry) = 0;
};

template<class ItemType>
class LinkedList : public ListInterface<ItemType>
{
private:
	Node<ItemType>* headPtr;
	int itemCount;

	Node<ItemType>* getNodeAt(int position) const;
public:
	LinkedList();
	LinkedList(const LinkedList<ItemType>& aList);
	~LinkedList();
	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const;
	void setEntry(int position, const ItemType& newEntry);
};

template<class ItemType>
class ArrayList : public ListInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 100;
	ItemType* items;
	int itemCount;
	int maxItems;
public:
	ArrayList();
	ArrayList(const ArrayList& aList);
	~ArrayList();
	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const ItemType& newEntry);
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const;
	void setEntry(int position, const ItemType& newEntry);
};

//=================================================================================================
// LinkedList
//=================================================================================================
template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList)
{
	itemCount = aList.itemCount;
	Node<ItemType>* origChainPtr = aList.headPtr; // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty; so is copy
	else
	{
		// Copy first node
		headPtr = new Node<ItemType>(origChainPtr->item);

		// Copy remaining nodes
		Node<ItemType>* newChainPtr = headPtr;
		origChainPtr = origChainPtr->next;
		while (origChainPtr != nullptr)
		{
			newChainPtr->next = new Node<ItemType>(origChainPtr->item);
			newChainPtr = newChainPtr->next;
			origChainPtr = origChainPtr->next;
		}

		newChainPtr->next = nullptr; // Flag end of new chain
	}
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	bool ableToInsert = (1 <= newPosition) && (newPosition <= itemCount + 1);
	if(ableToInsert)
	{	//create a new node
		Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
		// attach new node to chain
		if(newPosition == 1)
		{
			newNodePtr->next = headPtr;
			headPtr = newNodePtr;
		}
		else
		{
			Node<ItemType>* prevNodePtr = getNodeAt(newPosition - 1);
			newNodePtr->next = prevNodePtr->next;
			prevNodePtr->next = newNodePtr;
		}
		itemCount++;
	}
	return ableToInsert;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
{
	bool ableToRemove = (1 <= position) && (position <= itemCount);
	if(ableToRemove)
	{
		Node<ItemType>* curPtr = nullptr;
		if(position == 1)
		{
			curPtr = headPtr;
			headPtr = headPtr->next;
		}
		else
		{
			Node<ItemType>* prevNodePtr = getNodeAt(position - 1);
			curPtr = prevNodePtr->next;
			prevNodePtr->next = curPtr->next;
		}
		curPtr->next = nullptr;
		delete curPtr;
		curPtr = nullptr;
		itemCount--;
	}
	return ableToRemove;
}

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	while(!isEmpty())
		remove(1);
}

template<class ItemType>
ItemType LinkedList<ItemType>::getEntry(int position) const
{
	bool ableToGet = (1 <= position) && (position <= itemCount);
	if(ableToGet)
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		return nodePtr->item;
	}
	else
		throw logic_error("Precondition Violated Exception: getEntry() called with an empty list or invalid position.\n");
}

template<class ItemType>
void LinkedList<ItemType>::setEntry(int position, const ItemType& newEntry)
{
	bool ableToSet = (1 <= position) && (position <= itemCount);
	if(ableToSet)
	{
		Node<ItemType>* nodePtr = getNodeAt(position);
		nodePtr->item = newEntry;
	}
	else
		throw logic_error("Precondition Violated Exception: setEntry() called with an empty list or invalid position.\n");
}

template<class ItemType>
Node<ItemType>* LinkedList<ItemType>::getNodeAt(int position) const
{
	if((position < 1) && (position > itemCount))
		throw out_of_range("out_of_range exception called at getNodeAt()\n");

	Node<ItemType>* curPtr = headPtr;
	for (int i = 1; i < position; i++)
		curPtr = curPtr->next;
	return curPtr;
}

//=================================================================================================
// ArrayList
//=================================================================================================
template<class ItemType>
ArrayList<ItemType>::ArrayList() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	items = new ItemType[maxItems];
}

template<class ItemType>
ArrayList<ItemType>::ArrayList(const ArrayList& aList)
{
	itemCount = aList.itemCount;
	maxItems = aList.maxItems;
	items = new ItemType[maxItems];
	for (int i = 0; i < itemCount; i++) {
		items[i] = aList.items[i];
	}
}

template<class ItemType>
ArrayList<ItemType>::~ArrayList()
{
	delete[] items;
}

template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
int ArrayList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
bool ArrayList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
	bool ableToInsert = (1 <= newPosition) && (newPosition <= itemCount + 1);
	if(ableToInsert)
	{
		bool hasRoomToAdd = (itemCount < maxItems);
		if(!hasRoomToAdd)
		{
			ItemType* oldArray = items;
			items = new ItemType[2 * maxItems];
			for(int i = 0; i < maxItems; i++)
				items[i] = oldArray[i];
			delete[] oldArray;
			maxItems *= 2;
		}
		// make room for new item by shifting
		for(int i = itemCount; i >= newPosition; i--)
			items[i] = items[i - 1];
		// insert new item
		items[newPosition - 1] = newEntry;
		itemCount++; // increase the size of the list by one
	}
	return ableToInsert;
}

template<class ItemType>
bool ArrayList<ItemType>::remove(int position)
{
	bool ableToRemove = (1 <= position) && (position <= itemCount);
	if(ableToRemove)
	{
		// delete item by shifting
		for(int i = position; i < itemCount; i++)
			items[i - 1] = items[i];
		itemCount--; // decrease count of entries
	}
	return ableToRemove;
}

template<class ItemType>
void ArrayList<ItemType>::clear()
{
	itemCount = 0;
}

template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const
{
	bool ableToGet = (1 <= position) && (position <= itemCount);
	if(ableToGet)
		return items[position - 1];
	else
		throw logic_error("Precondition Violated Exception: getEntry() called with an empty list or invalid position.\n");
}

template<class ItemType>
void ArrayList<ItemType>::setEntry(int position, const ItemType& newEntry)
{
	bool ableToSet = (1 <= position) && (position <= itemCount);
	if(ableToSet)
		items[position - 1] = newEntry;
	else
		throw logic_error("Precondition Violated Exception: setEntry() called with an empty list or invalid position.\n");
}
#endif // !_LIST_H_
