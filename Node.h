// Node.h
#ifndef _NODE_H_
#define _NODE_H_
template<class ItemType>
struct Node
{
	ItemType item;
	Node<ItemType>* next;
	Node();
	Node(const ItemType& anItem);
	Node(const ItemType& anItem, Node<ItemType>* nextNodePtr);
};

template<class ItemType>
Node<ItemType>::Node() : next(nullptr)
{
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr)
{
}

template<class ItemType>
Node<ItemType>::Node(const ItemType& anItem, Node<ItemType>* nextNodePtr)
	: item(anItem), next(nextNodePtr)
{
}
#endif // !_NODE_H_
