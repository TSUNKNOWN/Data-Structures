// BinarySearchTree.h
#ifndef _BINARY_SEARCH_TREE_H_
#define _BINARY_SEARCH_TREE_H_
#include "BinaryNode.h"

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

template<class ItemType>
class BinarySearchTree : public BinaryTreeInterface<ItemType>
{
private:
	BinaryNode<ItemType>* rootPtr;

protected:
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* treePtr) const;
	int getHeightHelper(BinaryNode<ItemType>* subTreePtr) const;
	int getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const;
	BinaryNode<ItemType>* insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr);
	BinaryNode<ItemType>* removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType& target, bool& success);
	BinaryNode<ItemType>* removeNode(BinaryNode<ItemType>* nodePtr);
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& inorderSuccessor);
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* subTreePtr, const ItemType& target) const;
	void inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const;
	void destroyTree(BinaryNode<ItemType>* subTreePtr);

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	BinarySearchTree();
	BinarySearchTree(const ItemType& rootItem);
	BinarySearchTree(const BinarySearchTree<ItemType>& aBSTree);
	virtual ~BinarySearchTree();

	//------------------------------------------------------------
	// Public BinaryTreeInterface Methods Section.
	//------------------------------------------------------------
	bool isEmpty() const;
	int getHeight() const;
	int getNumberOfNodes() const;
	ItemType getRootData() const;
	int add(const ItemType& newData);
	bool remove(const ItemType& target);
	void clear();
	ItemType getEntry(const ItemType& anEntry) const;
	bool contains(const ItemType& anEntry) const;

	//------------------------------------------------------------
	// Public Traversals Section.
	//------------------------------------------------------------
	void preorderTraverse(void visit(ItemType&)) const;
	void inorderTraverse(void visit(ItemType&)) const;
	void postorderTraverse(void visit(ItemType&)) const;
}; // end BinarySearchTree

//=================================================================================================
// BinarySearchTree
//=================================================================================================
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() : rootPtr(nullptr)
{
} // end default constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem)
{
	rootPtr = new BinaryNode<ItemType>(rootItem);
} // end constructor

template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>& aBTree)
{
	rootPtr = copyTree(aBTree.rootPtr);
} // end copy constructor

template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree()
{
	destroyTree(rootPtr);
} // end destructor

template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const
{
	return (rootPtr == nullptr);
}

template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() const
{
	return getHeightHelper(rootPtr);
}

// template<class ItemType>
// int BinarySearchTree<ItemType>::getNumberOfNodes() const
// {
// 	return getNumberOfNodesHelper(rootPtr);
// }

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getRootData() const
{
	if(isEmpty())
		throw logic_error("Precondition Violated Exception: getRootData() called with an empty tree.\n");

	return rootPtr->item;
}

template<class ItemType>
int BinarySearchTree<ItemType>::add(const ItemType& newData)
{
	BinaryNode<ItemType>* newNodePtr = new BinaryNode<ItemType>(newData);
	rootPtr = insertInorder(rootPtr, newNodePtr);

	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType& target)
{
	bool success = false;
	rootPtr = removeValue(rootPtr, target, success);
	return success;
}

// template<class ItemType>
// void BinarySearchTree<ItemType>::clear()
// {
// 	destroyTree(rootPtr);
// }

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType& anEntry) const
{
	BinaryNode<ItemType>* temp = findNode(rootPtr, anEntry);
	if(temp == nullptr)
		throw logic_error("Precondition Violated Exception: getEntry() called with an empty tree.\n");
	else
		return temp->item;
}

// template<class ItemType>
// bool BinarySearchTree<ItemType>::contains(const ItemType& anEntry) const
// {

// }

// template<class ItemType>
// void BinarySearchTree<ItemType>::preorderTraverse(void visit(ItemType&)) const
// {

// }

template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&)) const
{
	inorder(visit, rootPtr);
}

// template<class ItemType>
// void BinarySearchTree<ItemType>::postorderTraverse(void visit(ItemType&)) const
// {

// }

//=====================================================
/***** Protected BinarySearchTree Methods Section. *****/
//=====================================================
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::copyTree(const BinaryNode<ItemType>* treePtr) const
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
int BinarySearchTree<ItemType>::getHeightHelper(BinaryNode<ItemType>* subTreePtr) const
{
	if (subTreePtr == nullptr)
		return 0;
	else
		return 1 + max(getHeightHelper(subTreePtr->leftChildPtr),
					   getHeightHelper(subTreePtr->rightChildPtr));
}

// template<class ItemType>
// int BinarySearchTree<ItemType>::getNumberOfNodesHelper(BinaryNode<ItemType>* subTreePtr) const
// {

// }

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::insertInorder(BinaryNode<ItemType>* subTreePtr, BinaryNode<ItemType>* newNodePtr)
{
	if(subTreePtr == nullptr)
		return newNodePtr;
	else
	{
		if(newNodePtr->item < subTreePtr->item)
			subTreePtr->leftChildPtr = insertInorder(subTreePtr->leftChildPtr, newNodePtr);
		else
			subTreePtr->rightChildPtr = insertInorder(subTreePtr->rightChildPtr, newNodePtr);

		return subTreePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeValue(BinaryNode<ItemType>* subTreePtr, const ItemType& target, bool& success)
{
	if(subTreePtr == nullptr)
	{
		success = false;
		return nullptr;
	}
	else
	{
		if(subTreePtr->item == target)
		{
			subTreePtr = removeNode(subTreePtr);
			success = true;
		}
		else if(subTreePtr->item > target)
			subTreePtr->leftChildPtr = removeValue(subTreePtr->leftChildPtr, target, success);
		else // subTreePtr->item < target
			subTreePtr->rightChildPtr = removeValue(subTreePtr->rightChildPtr, target, success);

		return subTreePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeNode(BinaryNode<ItemType>* nodePtr)
{
	// nodePtr points to node N
	if(nodePtr->isLeaf()) // N is a leaf
	{
		delete nodePtr; // Remove N from the tree
		nodePtr = nullptr;
		return nullptr;
	}
	else if(nodePtr->rightChildPtr == nullptr) // N has only one left child C
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->leftChildPtr;
		delete nodePtr; // Remove N from the tree
		nodePtr = nullptr;
		return nodeToConnectPtr; // Make C the child of N's parent P
	}
	else if(nodePtr->leftChildPtr == nullptr) // N has only one right child C
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->rightChildPtr;
		delete nodePtr; // Remove N from the tree
		nodePtr = nullptr;
		return nodeToConnectPtr; // Make C the child of N's parent P
	}
	else // N has two childs
	{
		// Find S, the node that contains N's inorder successor
		// Copy the item from node S into node N
		// Remove S from the tree by using the previous techique for a leaf or a node with one child
		ItemType newNodeValue;
		nodePtr->rightChildPtr = removeLeftmostNode(nodePtr->rightChildPtr, newNodeValue);
		nodePtr->item = newNodeValue;
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType& inorderSuccessor)
{
	if(nodePtr->leftChildPtr == nullptr)
	{
		inorderSuccessor = nodePtr->item;
		return removeNode(nodePtr);
	}
	else
	{
		nodePtr->leftChildPtr = removeLeftmostNode(nodePtr->leftChildPtr, inorderSuccessor);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr, const ItemType& target) const
{
	if(subTreePtr == nullptr)
		return nullptr;
	else
	{
		if(subTreePtr->item == target)
			return subTreePtr;
		else if(subTreePtr->item > target)
			return findNode(subTreePtr->leftChildPtr, target);
		else // subTreePtr->item < target
			return findNode(subTreePtr->rightChildPtr, target);
	}
}
template<class ItemType>
void BinarySearchTree<ItemType>::inorder(void visit(ItemType&), BinaryNode<ItemType>* treePtr) const
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
void BinarySearchTree<ItemType>::destroyTree(BinaryNode<ItemType>* subTreePtr)
{
	if(subTreePtr != nullptr)
	{
		destroyTree(subTreePtr->leftChildPtr);
		destroyTree(subTreePtr->rightChildPtr);
		delete subTreePtr;
	} // end if
}
#endif // !_BINARY_SEARCH_TREE_H_
