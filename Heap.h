// Heap.h
#ifndef _HEAP_H_
#define _HEAP_H_
#include <cmath>
#include <stdexcept>
using namespace std;

template<class ItemType>
class HeapInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getNumberOfNodes() const = 0;
	virtual int getHeight() const = 0;
	virtual ItemType peekTop() const = 0;
	virtual bool add(const ItemType& newData) = 0;
	virtual bool remove() = 0;
	virtual void clear() = 0;
};

template<class ItemType>
class ArrayMaxHeap : public HeapInterface<ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 21;
	ItemType* items;
	int itemCount;
	int maxItems;
	void heapRebuild(int rootIndex);
public:
	ArrayMaxHeap();
	ArrayMaxHeap(const ArrayMaxHeap<ItemType>& aHeap);
	~ArrayMaxHeap();
	bool isEmpty() const;
	int getNumberOfNodes() const;
	int getHeight() const;
	ItemType peekTop() const;
	bool add(const ItemType& newData);
	bool remove();
	void clear();
};

//=================================================================================================
// ArrayMaxHeap
//=================================================================================================
template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap() : itemCount(0), maxItems(DEFAULT_CAPACITY)
{
	items = new ItemType[maxItems];
}

template<class ItemType>
ArrayMaxHeap<ItemType>::ArrayMaxHeap(const ArrayMaxHeap<ItemType>& aHeap)
{
	itemCount = aHeap.itemCount;
	maxItems = aHeap.maxItems;
	items = new ItemType[maxItems];
	for(int i = 0; i < itemCount; i++) {
		items[i] = aHeap.items[i];
	}
}

template<class ItemType>
ArrayMaxHeap<ItemType>::~ArrayMaxHeap()
{
	delete[] items;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::isEmpty() const
{
	return (itemCount == 0);
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getNumberOfNodes() const
{
	return itemCount;
}

template<class ItemType>
int ArrayMaxHeap<ItemType>::getHeight() const
{
	return ceil(log2(itemCount + 1));
}

template<class ItemType>
ItemType ArrayMaxHeap<ItemType>::peekTop() const
{
	if(isEmpty())
		throw logic_error("Precondition Violated Exception: peekTop() called with an empty heap.\n");

	return items[0];
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::add(const ItemType& newData)
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

	items[itemCount] = newData;

	int newDataIndex = itemCount;
	bool inPlace = false;
	while((newDataIndex > 0) && !inPlace)
	{
		int parentIndex = (newDataIndex - 1) / 2;
		if(items[newDataIndex] > items[parentIndex])
		{
			ItemType temp = items[newDataIndex];
			items[newDataIndex] = items[parentIndex];
			items[parentIndex] = temp;

			newDataIndex = parentIndex;
		}
		else
			inPlace = true;
	}
	itemCount++;

	return true;
}

template<class ItemType>
bool ArrayMaxHeap<ItemType>::remove()
{
	items[0] = items[itemCount - 1];
	itemCount--;
	heapRebuild(0);
	return true;
}

template<class ItemType>
void ArrayMaxHeap<ItemType>::clear()
{
	itemCount = 0;
}

// private member function of ArrayMaxHeap
template<class ItemType>
void ArrayMaxHeap<ItemType>::heapRebuild(int rootIndex)
{
	if(2 * rootIndex + 1 < itemCount) // the root is not a leaf (that is, it has a left child)
	{
		int largerChildIndex = 2 * rootIndex + 1; // left child index
		if(largerChildIndex + 1 < itemCount) // the root has a right child
		{
			int rightChildIndex = largerChildIndex + 1;
			if(items[rightChildIndex] > items[largerChildIndex])
				largerChildIndex = rightChildIndex;
		}

		if(items[rootIndex] < items[largerChildIndex])
		{	// swap
			ItemType temp = items[rootIndex];
			items[rootIndex] = items[largerChildIndex];
			items[largerChildIndex] = temp;

			heapRebuild(largerChildIndex);
		}
	}
}
#endif // !_HEAP_H_
