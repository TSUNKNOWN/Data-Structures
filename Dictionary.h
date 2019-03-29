// Dictionary.h
#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_
#include "BinarySearchTree.h"

template<class KeyType, class ItemType>
class DictionaryInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getNumberOfItems() const = 0;
	virtual bool add(const KeyType& searchKey, const ItemType& newEntry) = 0;
	virtual bool remove(const KeyType& searchKey) = 0;
	virtual void clear() const = 0;
	virtual ItemType getItem(const KeyType& searchKey) const = 0;
	virtual bool contains(const KeyType& searchKey) const = 0;
	virtual void traverse(void visit(ItemType&)) const = 0;
};

template<class KeyType, class ItemType>
class Entry
{
private:
	ItemType item;
	KeyType searchKey;

public:
	ItemType getItem() const;
	KeyType getKey() const;
	void setItem(const ItemType& newEntry);
	bool operator==(const Entry<KeyType, ItemType>& rightHandItem) const;
	bool operator> (const Entry<KeyType, ItemType>& rightHandItem) const;
};

template<class KeyType, class ItemType>
class ArrayDictionary : public DictionaryInterface<KeyType, ItemType>
{
private:
	static const int DEFAULT_CAPACITY = 21;
	Entry<KeyType, ItemType>* items; // array of dictionary entries
	int itemCount;
	int maxItems;
public:
	ArrayDictionary();
	ArrayDictionary(const ArrayDictionary<KeyType, ItemType>& aDict);
	~ArrayDictionary();
	bool isEmpty() const;
	int getNumberOfItems() const;
	bool add(const KeyType& searchKey, const ItemType& newEntry);
	bool remove(const KeyType& searchKey);
	void clear() const;
	ItemType getItem(const KeyType& searchKey) const;
	bool contains(const KeyType& searchKey) const;
	void traverse(void visit(ItemType&)) const;
};

template<class KeyType, class ItemType>
class TreeDictionary : public DictionaryInterface<KeyType, ItemType>
{
private:
	BinarySearchTree< Entry<KeyType, ItemType> > itemTree;
public:
	TreeDictionary();
	TreeDictionary(const TreeDictionary<KeyType, ItemType>& aDict);
	~TreeDictionary();
	bool isEmpty() const;
	int getNumberOfItems() const;
	bool add(const KeyType& searchKey, const ItemType& newEntry);
	bool remove(const KeyType& searchKey);
	void clear() const;
	ItemType getItem(const KeyType& searchKey) const;
	bool contains(const KeyType& searchKey) const;
	void traverse(void visit(ItemType&)) const;
};

//=================================================================================================
// Entry
//=================================================================================================
template<class KeyType, class ItemType>
ItemType Entry<KeyType, ItemType>::getItem() const
{
	return item;
}

template<class KeyType, class ItemType>
KeyType Entry<KeyType, ItemType>::getKey() const
{
	return searchKey;
}

template<class KeyType, class ItemType>
void Entry<KeyType, ItemType>::setItem(const ItemType& newEntry)
{
	item = newEntry;
}

template<class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator==(const Entry<KeyType, ItemType>& rightHandItem) const
{
	return (searchKey == rightHandItem.getKey());
}

template<class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator> (const Entry<KeyType, ItemType>& rightHandItem) const
{
	return (searchKey > rightHandItem.getKey());
}

template<class KeyType, class ItemType>
bool Entry<KeyType, ItemType>::operator< (const Entry<KeyType, ItemType>& rightHandItem) const
{
	return (searchKey < rightHandItem.getKey());
}

//=================================================================================================
// ArrayDictionary
//=================================================================================================
template<class KeyType, class ItemType>
bool ArrayDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
	bool ableToInsert = (itemCount < maxItems);
	if(ableToInsert)
	{
		int index = itemCount;
		while((index > 0) && (searchKey < items[index - 1].getKey()))
		{
			items[index] = items[index - 1];
			index--;
		}

		items[index] = Entry<KeyType, ItemType>(newItem, searchKey);
		itemCount++;
	}
	return ableToInsert;
}

//=================================================================================================
// TreeDictionary
//=================================================================================================
template<class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::add(const KeyType& searchKey, const ItemType& newItem)
{
	return itemTree.add(Entry<KeyType, ItemType>(newItem, searchKey));
}

template<class KeyType, class ItemType>
bool TreeDictionary<KeyType, ItemType>::remove(const KeyType& searchKey)
{
	return itemTree.remove(Entry<KeyType, ItemType>(ItemType(), searchKey));
}
#endif // !_DICTIONARY_H_
