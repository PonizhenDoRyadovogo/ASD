#include "BinaryTreeSearch.h"

//BinaryTreeSearch BinaryTreeSearch::clone() const
//{
//	return clone(root());
//}
//
//BinaryTreeSearch BinaryTreeSearch::clone(Node* root) const
//{
//	if (!root)
//		return *this;
//	BinaryTree clone = BinaryTree::clone(root);
//	BinaryTreeSearch searchTree;
//
//}

BinaryTree::Node* BinaryTreeSearch::find(Node* root, const int key) const
{
	if (!root)
		return nullptr;
	while (root && root->getKey() != key)
	{
		if (key < root->getKey())
			root = root->getLeft();
		else if (key > root->getKey())
			root = root->getRight();
	}
	return root;
}

bool BinaryTreeSearch::remove(const int key)
{
	return false;
}

BinaryTree::Node* BinaryTreeSearch::_addNode(Node* root, const int key) 
{
	if (!root)
	{
		root = new Node(key);
	}
	else if (key < root->getKey())
	{
		root->setLeft(_addNode(root->getLeft(), key));
	}
	else
	{
		root->setRight(_addNode(root->getRight(), key));
	}
	return root;
}
