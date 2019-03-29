// BinaryNode.h
#ifndef _BINARY_NODE_H_
#define _BINARY_NODE_H_
template<class ItemType>
struct BinaryNode
{
	ItemType item; // data portion
	BinaryNode<ItemType>* leftChildPtr; // pointer to left child
	BinaryNode<ItemType>* rightChildPtr; // pointer to right child
	BinaryNode();
	BinaryNode(const ItemType& anItem);
	BinaryNode(const ItemType& anItem, BinaryNode<ItemType>* leftNodePtr, BinaryNode<ItemType>* rightNodePtr);
	bool isLeaf() const;
};

template<class ItemType>
BinaryNode<ItemType>::BinaryNode() : leftChildPtr(nullptr), rightChildPtr(nullptr)
{
}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem)
	: item(anItem), leftChildPtr(nullptr), rightChildPtr(nullptr)
{
}

template<class ItemType>
BinaryNode<ItemType>::BinaryNode(const ItemType& anItem,
								 BinaryNode<ItemType>* leftNodePtr,
								 BinaryNode<ItemType>* rightNodePtr)
	: item(anItem), leftChildPtr(leftNodePtr), rightChildPtr(rightNodePtr)
{
}

template<class ItemType>
bool BinaryNode<ItemType>::isLeaf() const
{
	return ((leftChildPtr == nullptr) && (rightChildPtr == nullptr));
}
#endif // !_BINARY_NODE_H_
