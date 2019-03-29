// Bag.h
#ifndef _BAG_H_
#define _BAG_H_
#include "Node.h"

template<typename ItemType>
class BagInterface
{
public:
	virtual int getCurrentSize() const = 0;
	virtual bool isEmpty() const = 0;
	virtual bool add(const ItemType& newEntry) = 0;
	virtual bool remove(const ItemType& anEntry) = 0;
	virtual void clear() = 0;
	virtual int getFrequencyOf(const ItemType& anEntry) const = 0;
	virtual bool contains(const ItemType& anEntry) const = 0;
	virtual void print() const = 0;
};

template<typename ItemType>
class LinkedBag : public BagInterface<ItemType>
{
private:
	Node<ItemType>* headPtr; // Pointer to first node
	int itemCount;           // Current count of bag items
	Node<ItemType>* getPointerTo(const ItemType& target) const;
							 // Returns either a pointer to the node containing a given entry
							 // or the null pointer if the entry is not in the bag.
public:
	LinkedBag();
	LinkedBag(const LinkedBag<ItemType>& aBag); // Copy constructor
	virtual ~LinkedBag();                       // Destructor should be virtual
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	void print() const;
};

template<typename ItemType>
class ArrayBag : public BagInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 6;
	ItemType* items;
	int itemCount;
	int maxItems;
	int getIndexOf(const ItemType& target) const;

public:
	ArrayBag();
	ArrayBag(const ArrayBag<ItemType>& aBag);
	~ArrayBag();
	int getCurrentSize() const;
	bool isEmpty() const;
	bool add(const ItemType& newEntry);
	bool remove(const ItemType& anEntry);
	void clear();
	bool contains(const ItemType& anEntry) const;
	int getFrequencyOf(const ItemType& anEntry) const;
	void print() const;
	const ArrayBag<ItemType>& operator=(const ArrayBag<ItemType>& aBag);
};

//=================================================================================================
// LinkedBag
//=================================================================================================
template<typename ItemType>
LinkedBag<ItemType>::LinkedBag() : headPtr(nullptr), itemCount(0)
{
}

template<typename ItemType>
LinkedBag<ItemType>::LinkedBag(const LinkedBag<ItemType>& aBag)
{
	itemCount = aBag.itemCount;
	Node<ItemType>* origChainPtr = aBag.headPtr; // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr = nullptr;  // Original bag is empty; so is copy
	else
	{
		// Copy first node
		Node<ItemType>* newChainPtr = headPtr;
		newChainPtr = new Node<ItemType>(origChainPtr->item);

		// Copy remaining nodes
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

template<typename ItemType>
LinkedBag<ItemType>::~LinkedBag()
{
	clear();
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}

template<typename ItemType>
bool LinkedBag<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<typename ItemType>
bool LinkedBag<ItemType>::add(const ItemType& newEntry)
{
	// Add to beginning of chain: new node references rest of chain;
	// (headPtr is null if chain is empty)        
	Node<ItemType>* newNodePtr = new Node<ItemType>();
	newNodePtr->item = newEntry;
	newNodePtr->next = headPtr;  // New node points to chain

	headPtr = newNodePtr;          // New node is now first node
	itemCount++;

	return true;
}

template<typename ItemType>
bool LinkedBag<ItemType>::remove(const ItemType& anEntry)
{
	Node<ItemType>* entryNodePtr = getPointerTo(anEntry);
	bool canRemoveItem = (!isEmpty() && (entryNodePtr != nullptr));
	if (canRemoveItem)
	{
		// Copy data from first node to located node
		entryNodePtr->item = headPtr->item;

		// Delete first node
		Node<ItemType>* nodeToDeletePtr = headPtr;
		headPtr = headPtr->next;

		// Releasing the space to the system
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		itemCount--;
	}

	return canRemoveItem;
}

template<typename ItemType>
void LinkedBag<ItemType>::clear()
{
	Node<ItemType>* nodeToDeletePtr = headPtr;
	while (headPtr != nullptr)
	{
		headPtr = headPtr->next;

		// Releasing the space to the system
		nodeToDeletePtr->next = nullptr;
		delete nodeToDeletePtr;

		nodeToDeletePtr = headPtr;
	}
	// headPtr is nullptr; nodeToDeletePtr is nullptr

	itemCount = 0;
}

template<typename ItemType>
bool LinkedBag<ItemType>::contains(const ItemType& anEntry) const
{
	return (getPointerTo(anEntry) != nullptr);
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	Node<ItemType>* curPtr = headPtr;
	while (curPtr != nullptr)
	{
		if (anEntry == curPtr->item)
			frequency++;
		curPtr = curPtr->next;
	}

	return frequency;
}

template<typename ItemType>
void LinkedBag<ItemType>::print() const
{
	Node<ItemType>* curPtr = headPtr;
	for (int i = 0 ; i < itemCount ; i++) {
		cout << curPtr->item << " ";
		curPtr = curPtr->next;
	}
	cout << endl;
}

// private
// Returns either a pointer to the node containing a given entry
// or the null pointer if the entry is not in the bag.
template<typename ItemType>
Node<ItemType>* LinkedBag<ItemType>::getPointerTo(const ItemType& anEntry) const
{
	bool found = false;
	Node<ItemType>* curPtr = headPtr;

	while (!found && (curPtr != nullptr))
	{
		if (anEntry == curPtr->item)
			found = true;
		else
			curPtr = curPtr->next;
	}

	return curPtr;
}

//=================================================================================================
// ArrayBag
//=================================================================================================
template<typename ItemType>
ArrayBag<ItemType>::ArrayBag() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	items = new ItemType[DEFAULT_CAPACITY];
}

template<typename ItemType>
ArrayBag<ItemType>::ArrayBag(const ArrayBag<ItemType>& aBag) {
	this->itemCount = aBag.itemCount;
	this->maxItems = aBag.maxItems;
	this->items = new ItemType[this->maxItems];
	for (int i = 0 ; i < this->itemCount ; i++) {
		this->items[i] = aBag.items[i];
	}
}

template<typename ItemType>
ArrayBag<ItemType>::~ArrayBag()
{
	delete[] items;
}

template<typename ItemType>
int ArrayBag<ItemType>::getCurrentSize() const
{
	return itemCount;
}

template<typename ItemType>
bool ArrayBag<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<typename ItemType>
bool ArrayBag<ItemType>::add(const ItemType& newEntry)
{
	bool hasRoomToAdd = (itemCount < maxItems);
	if (!hasRoomToAdd)
	{
		ItemType* oldArray = items;
		items = new ItemType[2 * maxItems];
		for (int i = 0; i < maxItems; i++)
			items[i] = oldArray[i];
		delete[] oldArray;
		maxItems *= 2;
	}
	items[itemCount] = newEntry;
	itemCount++;
	
	return true;
}

template<typename ItemType>
bool ArrayBag<ItemType>::remove(const ItemType& anEntry)
{
	int locatedIndex = getIndexOf(anEntry);
	bool canRemoveItem = (locatedIndex > -1);
	if (canRemoveItem)
	{
		itemCount--;
		items[locatedIndex] = items[itemCount];
	}
	return canRemoveItem;
}

template<typename ItemType>
void ArrayBag<ItemType>::clear()
{
	itemCount = 0;
}

template<typename ItemType>
bool ArrayBag<ItemType>::contains(const ItemType& anEntry) const
{
	return getIndexOf(anEntry) > -1;
}

template<typename ItemType>
int ArrayBag<ItemType>::getFrequencyOf(const ItemType& anEntry) const
{
	int frequency = 0;
	int curIndex = 0;
	while (curIndex < itemCount)
	{
		if (items[curIndex] == anEntry)
			frequency++;
		curIndex++;
	}
	return frequency;
}

template<typename ItemType>
void ArrayBag<ItemType>::print() const
{
	for (int i = 0; i < itemCount; i++)
		cout << items[i] << " ";
	cout << endl;
}

template<typename ItemType>
const ArrayBag<ItemType>& ArrayBag<ItemType>::operator=(const ArrayBag<ItemType>& aBag)
{
	if (this != &aBag) {
		if (this->itemCount != aBag.itemCount) {
			if (this->maxItems != aBag.maxItems) {
				this->maxItems = aBag.maxItems;
				delete[] this->items;
				this->items = new ItemType[this->maxItems];
			}
			this->itemCount = aBag.itemCount;
		}
		for (int i = 0; i < this->itemCount; i++) {
			this->items[i] = aBag.items[i];
		}
	}
	return *this;
}

// private
template<typename ItemType>
int ArrayBag<ItemType>::getIndexOf(const ItemType& target) const
{
	for (int i = 0; i < itemCount; i++) {
		if (items[i] == target)
			return i;
	}
	return -1;
}
#endif // !_BAG_H_
