// SortedList.h
// This SortedList is listed from SMALL to BIG
// ex: 1 < 3 < 5 < 7
//	   a < f < m < s
#ifndef _SORTED_LIST_H_
#define _SORTED_LIST_H_
#include <stdexcept>
#include "Node.h"
using namespace std;

template<class ItemType>
class SortedListInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getLength() const = 0;
	virtual bool remove(int position) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry(int position) const = 0;
	virtual void insertSorted(const ItemType& newEntry) = 0;
	virtual bool removeSorted(const ItemType& anEntry) = 0;
	virtual int getPosition(const ItemType& anEntry) const = 0;
};

template<class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private:
	Node<ItemType>* headPtr;
	int itemCount;

	Node<ItemType>* getNodeAt(int position) const;
	Node<ItemType>* getNodeBefore(const ItemType& anEntry) const;
public:
	LinkedSortedList();
	LinkedSortedList(const LinkedSortedList<ItemType>& aSList);
	~LinkedSortedList();
	bool isEmpty() const;
	int getLength() const;
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const;
	void insertSorted(const ItemType& newEntry);
	bool removeSorted(const ItemType& anEntry);
	int getPosition(const ItemType& anEntry) const;
};

template<class ItemType>
class ArraySortedList : public SortedListInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 100;
	ItemType* items;
	int itemCount;
	int maxItems;
public:
	ArraySortedList();
	ArraySortedList(const ArraySortedList& aSList);
	~ArraySortedList();
	bool isEmpty() const;
	int getLength() const;
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const;
	void insertSorted(const ItemType& newEntry);
	bool removeSorted(const ItemType& anEntry);
	int getPosition(const ItemType& anEntry) const;
};

//=================================================================================================
// LinkedSortedList
//=================================================================================================
template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aSList)
{
	itemCount = aSList.itemCount;
	Node<ItemType>* origChainPtr = aSList.headPtr; // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original SList is empty; so is copy
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
LinkedSortedList<ItemType>::~LinkedSortedList()
{
	clear();
}

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position)
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
void LinkedSortedList<ItemType>::clear()
{
	while(!isEmpty())
		remove(1);
}

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const
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
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	Node<ItemType>* prevPtr = getNodeBefore(newEntry);

	if(isEmpty() || (prevPtr == nullptr))
	{
		newNodePtr->next = headPtr;
		headPtr = newNodePtr;
	}
	else
	{
		Node<ItemType>* aftPtr = prevPtr->next;
		newNodePtr->next = aftPtr;
		prevPtr->next = newNodePtr;
	}

	itemCount++;
}

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType& anEntry)
{
	if(headPtr == nullptr) // empty sorted list
		return false;
	else if(headPtr->item == anEntry) // bingo at first one
	{
		Node<ItemType>* targetPtr = headPtr;
		headPtr = headPtr->next;

		targetPtr->next = nullptr;
		delete targetPtr;
		targetPtr = nullptr;

		itemCount--;
		return true;
	}
	else
	{
		Node<ItemType>* prevPtr = getNodeBefore(anEntry);
		Node<ItemType>* targetPtr = prevPtr->next;
		bool ableToRemoveSorted = (targetPtr != nullptr) &&
								  (targetPtr->item == anEntry);
		if(ableToRemoveSorted)
		{
			prevPtr->next = targetPtr->next;

			targetPtr->next = nullptr;
			delete targetPtr;
			targetPtr = nullptr;

			itemCount--;
		}
		return ableToRemoveSorted;
	}
}

template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType& anEntry) const
{
	Node<ItemType>* curPtr = headPtr;
	int positionCnt = 1;

	while((curPtr != nullptr) && (anEntry > curPtr->item))
	{
		curPtr = curPtr->next;
		positionCnt++;
	}
	if(curPtr == nullptr) // empty list or traverse to the end
		return -positionCnt;
	else if (anEntry < curPtr->item) // not bingo
		return -positionCnt;
	else  // anEntry == curPtr->item // bingo
		return positionCnt;
}

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeAt(int position) const
{
	if((position < 1) || (position > itemCount))
		throw out_of_range("out_of_range exception called at getNodeAt()\n");

	Node<ItemType>* curPtr = headPtr;
	for (int i = 1; i < position; i++)
		curPtr = curPtr->next;
	return curPtr;
}

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
	Node<ItemType>* curPtr = headPtr;
	Node<ItemType>* prevPtr = nullptr;

	while((curPtr != nullptr) && (anEntry > curPtr->item))
	{
		prevPtr = curPtr;
		curPtr = curPtr->next;
	}

	return prevPtr;
}

//=================================================================================================
// ArraySortedList
//=================================================================================================
template<class ItemType>
ArraySortedList<ItemType>::ArraySortedList() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	items = new ItemType[maxItems];
}

template<class ItemType>
ArraySortedList<ItemType>::ArraySortedList(const ArraySortedList& aSList)
{
	itemCount = aSList.itemCount;
	maxItems = aSList.maxItems;
	items = new ItemType[maxItems];
	for (int i = 0; i < itemCount; i++) {
		items[i] = aSList.items[i];
	}
}

template<class ItemType>
ArraySortedList<ItemType>::~ArraySortedList()
{
	delete[] items;
}

template<class ItemType>
bool ArraySortedList<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
int ArraySortedList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
bool ArraySortedList<ItemType>::remove(int position)
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
void ArraySortedList<ItemType>::clear()
{
	itemCount = 0;
}

template<class ItemType>
ItemType ArraySortedList<ItemType>::getEntry(int position) const
{
	bool ableToGet = (1 <= position) && (position <= itemCount);
	if(ableToGet)
		return items[position - 1];
	else
		throw logic_error("Precondition Violated Exception: getEntry() called with an empty list or invalid position.\n");
}

template<class ItemType>
void ArraySortedList<ItemType>::insertSorted(const ItemType& newEntry)
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
	int newPosition = 1;
	for (int i = 0; i < itemCount; i++)
	{
		if(newEntry <= items[i])
			break;
		newPosition++;
	}
	// make room for new item by shifting
	for(int i = itemCount; i >= newPosition; i--)
		items[i] = items[i - 1];
	// insert new item
	items[newPosition - 1] = newEntry;
	itemCount++; // increase the size of the list by one
}

template<class ItemType>
bool ArraySortedList<ItemType>::removeSorted(const ItemType& anEntry)
{
	int position = 1;
	for(int i = 0; i < itemCount; i++)
	{
		if(anEntry == items[i])
		{
			position = i + 1;
			break;
		}
		else if(anEntry < items[i])
			return false;
	}
	// delete item by shifting
	for(int i = position; i < itemCount; i++)
		items[i - 1] = items[i];
	itemCount--; // decrease count of entries
	return true;
}

template<class ItemType>
int ArraySortedList<ItemType>::getPosition(const ItemType& anEntry) const
{
	for(int i = 0; i < itemCount; i++)
	{
		if(anEntry == items[i])
		{
			return i + 1;
		}
		else if(anEntry < items[i])
			return -(i + 1);
	}
	return -(itemCount + 1);
}
#endif // !_SORTED_LIST_H_
