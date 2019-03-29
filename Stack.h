// Stack.h
#ifndef _STACK_H_
#define _STACK_H_
#include <stdexcept>
#include "Node.h"
using namespace std;

template<class ItemType>
class StackInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual bool push(const ItemType& newEntry) = 0;
	virtual bool pop() = 0;
	virtual ItemType peek() const = 0;
};

template<class ItemType>
class LinkedStack : public StackInterface<ItemType>
{
private:
	Node<ItemType>* topPtr;
public:
	LinkedStack();
	LinkedStack(const LinkedStack<ItemType>& aStack);	
	~LinkedStack();
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;
};

template<class ItemType>
class ArrayStack : public StackInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 10;
	ItemType* items;
	int top;
	int maxItems;
public:
	ArrayStack();
	ArrayStack(const ArrayStack& aStack);
	~ArrayStack();
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop();
	ItemType peek() const;
};

//=================================================================================================
// LinkedStack
//=================================================================================================
template<class ItemType>
LinkedStack<ItemType>::LinkedStack() : topPtr(nullptr)
{
}

template<class ItemType>
LinkedStack<ItemType>::LinkedStack(const LinkedStack<ItemType>& aStack)
{
	Node<ItemType>* origChainPtr = aStack.topPtr;
	if (origChainPtr == nullptr)
		topPtr = nullptr;
	else
	{	// copy first node
		topPtr = new Node<ItemType>(origChainPtr->item);

		// copy remaining nodes
		Node<ItemType>* newChainPtr = topPtr;
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
LinkedStack<ItemType>::~LinkedStack()
{
	while (!isEmpty())
		pop();
}

template<class ItemType>
bool LinkedStack<ItemType>::isEmpty() const
{
	return (topPtr == nullptr);
}

template<class ItemType>
bool LinkedStack<ItemType>::push(const ItemType& newItem)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newItem, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;

	return true;
}

template<class ItemType>
bool LinkedStack<ItemType>::pop()
{
	if (!isEmpty())
	{
		Node<ItemType>* nodeToDeletePtr = topPtr;
		topPtr = topPtr->next;

		nodeToDeletePtr->next = nullptr;
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		return true;
	}
	return false;
}

template<class ItemType>
ItemType LinkedStack<ItemType>::peek() const
{
	if (isEmpty())
		throw logic_error("Precondition Violated Exception: peek() called with an empty stack.\n");

	return topPtr->item;
}

//=================================================================================================
// ArrayStack
//=================================================================================================
template<class ItemType>
ArrayStack<ItemType>::ArrayStack() : top(-1), maxItems(DEFAULT_CAPACITY)
{
	items = new ItemType[maxItems];
}

template<class ItemType>
ArrayStack<ItemType>::ArrayStack(const ArrayStack& aStack)
{
	top = aStack.top;
	maxItems = aStack.maxItems;
	items = new ItemType[maxItems];
	for (int i = 0 ; i <= top ; i++) {
		items[i] = aStack.items[i];
	}
}

template<class ItemType>
ArrayStack<ItemType>::~ArrayStack()
{
	delete[] items;
}

template<class ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
	return (top < 0);
}

template<class ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry)
{
	bool hasRoomToAdd = (top < maxItems - 1);
	if (!hasRoomToAdd)
	{
		ItemType* oldArray = items;
		items = new ItemType[2 * maxItems];
		for (int i = 0; i < maxItems; i++)
			items[i] = oldArray[i];
		delete[] oldArray;
		maxItems *= 2;
	}
	top++;
	items[top] = newEntry;

	return true;
}

template<class ItemType>
bool ArrayStack<ItemType>::pop()
{
	if (!isEmpty())
	{
		top--;
		return true;
	}
	return false;
}

template<class ItemType>
ItemType ArrayStack<ItemType>::peek() const
{
	if (isEmpty())
		throw logic_error("Precondition Violated Exception: peek() called with an empty stack.\n");

	return items[top];
}
#endif // !_STACK_H_
