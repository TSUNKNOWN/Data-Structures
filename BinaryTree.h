// BinaryTree.h
#ifndef _BINARY_TREE_H_
#define _BINARY_TREE_H_
#include <stdexcept>
#include <algorithm>
#include "BinaryNode.h"
using namespace std;

template<class ItemType>
class BinaryTreeInterface
{
public:
	virtual bool isEmpty() const = 0;
	virtual int getHeight() const = 0;
	virtual int getNumberOfNodes() const = 0;
	virtual ItemType getRootData() const = 0;
	virtual void setRootData(const ItemType& newData) = 0;
	virtual bool add(const ItemType& newData) = 0;
	virtual bool remove(const ItemType& data) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry(const ItemType& anEntry) const = 0;
	virtual bool contains(const ItemType& anEntry) const = 0;
	virtual void preorderTraverse(void visit(ItemType&)) const = 0;
	virtual void inorderTraverse(void visit(ItemType&)) const = 0;
	virtual void postorderTraverse(void visit(ItemType&)) const = 0;
};

//=================================================================================================
// Array-Based Binary Tree
//=================================================================================================
// template<class ItemType>
// struct TreeNode
// {
// 	ItemType item;  // data portion
// 	int leftChild;  // index to left child
// 	int rightChild; // index to right child
// 	TreeNode();
// 	TreeNode(const ItemType& nodeItem, int left, int right);
// 	//...
// };

// template<class ItemType>
// class BinaryArrayTree : public BinaryTreeInterface<ItemType>
// {
// private:
// 	TreeNode<ItemType> tree[MAX_NODES]; // array of tree nodes
// 	int root; // index of root
// 	int free; // index of free list
// public:
// 	//------------------------------------------------------------
// 	// Constructor and Destructor Section.
// 	//------------------------------------------------------------
// 	BinaryArrayTree();
// 	BinaryArrayTree(const BinaryArrayTree<ItemType>& aBTree);
// 	virtual ~BinaryArrayTree();

// 	//------------------------------------------------------------
// 	// Public BinaryTreeInterface Methods Section.
// 	//------------------------------------------------------------
// 	bool isEmpty() const;
// 	int getHeight() const;
// 	int getNumberOfNodes() const;
// 	ItemType getRootData() const;
// 	void setRootData(const ItemType& newData);
// 	bool add(const ItemType& newData); // Adds a node
// 	bool remove(const ItemType& data); // Removes a node
// 	void clear();
// 	ItemType getEntry(const ItemType& anEntry) const;
// 	bool contains(const ItemType& anEntry) const;

// 	//------------------------------------------------------------
// 	// Public Traversals Section.
// 	//------------------------------------------------------------
// 	void preorderTraverse(void visit(ItemType&)) const;
// 	void inorderTraverse(void visit(ItemType&)) const;
// 	void postorderTraverse(void visit(ItemType&)) const;

// 	//------------------------------------------------------------
// 	// Overloaded Operator Section.
// 	//------------------------------------------------------------
// 	const BinaryArrayTree<ItemType>& operator= (const BinaryArrayTree<ItemType>& rightHandSide);
// }; // end BinaryArrayTree

//=================================================================================================
// Link-Based Binary Tree
//=================================================================================================
template<class ItemType>
class BinaryNodeTree : public BinaryTreeInterface<ItemType>
{
private:
	BinaryNode<ItemType>* rootPtr;

protected:
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;
	int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;
	int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;
	BinaryNode<ItemType>* balancedAdd(BinaryNode<ItemType>* subTreePtr,
									  BinaryNode<ItemType>* newNodePtr);
	void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
	void destroyTree(BinaryNode<ItemType>* subTreePtr);

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinaryNodeTree();
	BinaryNodeTree(const ItemType& rootItem);
	BinaryNodeTree(const ItemType& rootItem,
				   const BinaryNodeTree<ItemType>* leftTreePtr,
				   const BinaryNodeTree<ItemType>* rightTreePtr);
	BinaryNodeTree(const BinaryNodeTree<ItemType>& aBTree);
	virtual ~BinaryNodeTree();

	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const;
	void setRootData(const ItemType& newData);
	bool add(const ItemType& newData); // Adds a node
	bool remove(const ItemType& data); // Removes a node
	void clear();
	ItemType getEntry(const ItemType& anEntry) const;
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;

	//------------------------------------------------------------
	// Overloaded Operator Section.
	//------------------------------------------------------------
	const BinaryNodeTree<ItemType>& operator= (const BinaryNodeTree<ItemType>& rightHandSide);
}; // end BinaryNodeTree

//=================================================================================================
// BinaryNodeTree
//=================================================================================================
template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree() : rootPtr(nullptr)
{
} // end default constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem);
} // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const ItemType& rootItem,
										 const BinaryNodeTree<ItemType>* leftTreePtr,
										 const BinaryNodeTree<ItemType>* rightTreePtr)
{
	rootPtr = new BinaryNode<ItemType>(rootItem, copyTree(leftTreePtr->rootPtr), copyTree(rightTreePtr->rootPtr));
} // end constructor

template<class ItemType>
BinaryNodeTree<ItemType>::BinaryNodeTree(const BinaryNodeTree<ItemType>& aBTree)
{
	rootPtr = copyTree(aBTree.rootPtr);
} // end copy constructor

template<class ItemType>
BinaryNodeTree<ItemType>::~BinaryNodeTree()
{
	destroyTree(rootPtr);
} // end destructor

template<class ItemType>
bool BinaryNodeTree<ItemType>::isEmpty() const
{
	return (rootPtr == nullptr);
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

// template<class ItemType>
// int BinaryNodeTree<ItemType>::getNumberOfNodes() const
// {
// 	return getNumberOfNodesHelper(rootPtr);
// }

template<class ItemType>
ItemType BinaryNodeTree<ItemType>::getRootData() const
{
	if(isEmpty())
		throw logic_error("Precondition Violated Exception: getRootData() called with an empty tree.\n");

	return rootPtr->item;
}

template<class ItemType>
void BinaryNodeTree<ItemType>::setRootData(const ItemType& newData)
{
	if(isEmpty())
		rootPtr = new BinaryNode<ItemType>(newData);
	else
		rootPtr->item = newData;
}

template<class ItemType>
bool BinaryNodeTree<ItemType>::add(const ItemType& newData)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = balancedAdd(rootPtr, newNodePtr);

	return true;
}

// template<class ItemType>
// bool BinaryNodeTree<ItemType>::remove(const ItemType& data)
// {

// }

// template<class ItemType>
// void BinaryNodeTree<ItemType>::clear()
// {
// 	destroyTree(rootPtr);
// }

// template<class ItemType>
// ItemType BinaryNodeTree<ItemType>::getEntry(const ItemType& anEntry) const
// {

// }

// template<class ItemType>
// bool BinaryNodeTree<ItemType>::contains(const ItemType& anEntry) const
// {

// }

// template<class ItemType>
// void BinaryNodeTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
// {

// }

template<class ItemType>
void BinaryNodeTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
}

// template<class ItemType>
// void BinaryNodeTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
// {

// }

// const BinaryNodeTree<ItemType>& BinaryNodeTree<ItemType>::operator= (const BinaryNodeTree<ItemType>& rightHandSide)
// {

// }

//=====================================================
/***** Protected BinaryNodeTree Methods Section. *****/
//=====================================================
template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
{
	BinaryNode<ItemType>* newTreePtr = nullptr;

	// Copy tree nodes during a preorder traversal
	if(treePtr != nullptr)
	{	// Copy node
		newTreePtr = new BinaryNode<ItemType>(treePtr->item);
		newTreePtr->leftChildPtr = copyTree(treePtr->leftChildPtr);
		newTreePtr->rightChildPtr = copyTree(treePtr->rightChildPtr);
	} // end if

	return newTreePtr;
}

template<class ItemType>
int BinaryNodeTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + max(getHeightHelper(subTreePtr->leftChildPtr),
					   getHeightHelper(subTreePtr->rightChildPtr));
}

// template<class ItemType>
// int BinaryNodeTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
// {

// }

template<class ItemType>
BinaryNode<ItemType>* BinaryNodeTree<ItemType>::balancedAdd(BinaryNode<ItemType>* subTreePtr,
															BinaryNode<ItemType>* newNodePtr)
{
	if(subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		BinaryNode<ItemType>* leftPtr = subTreePtr->leftChildPtr;
		BinaryNode<ItemType>* rightPtr = subTreePtr->rightChildPtr;

		if(getHeightHelper(leftPtr) > getHeightHelper(rightPtr))
		{
			rightPtr = balancedAdd(rightPtr, newNodePtr);
			subTreePtr->rightChildPtr = rightPtr;
		}
		else
		{
			leftPtr = balancedAdd(leftPtr, newNodePtr);
			subTreePtr->leftChildPtr = leftPtr;
		}

		return subTreePtr;
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
{
	if(treePtr != nullptr)
	{
		inorder(visit, treePtr->leftChildPtr);
		ItemType theItem = treePtr->item;
		visit(theItem);
		// treePtr->item = theItem;
		inorder(visit, treePtr->rightChildPtr);
	}
}

template<class ItemType>
void BinaryNodeTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
	if(subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->leftChildPtr);
		destroyTree(subTreePtr->rightChildPtr);
		delete subTreePtr;
	} // end if
}
#endif // !_BINARY_TREE_H_
