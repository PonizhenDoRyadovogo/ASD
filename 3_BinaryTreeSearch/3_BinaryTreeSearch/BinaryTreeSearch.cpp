#include "BinaryTreeSearch.h"

BinaryTreeSearch BinaryTreeSearch::clone() const
{
	return clone(m_root);
}

BinaryTreeSearch BinaryTreeSearch::clone(Node* root) const
{
	BinaryTree tempTree = BinaryTree::clone();
	BinaryTreeSearch newSearchTree;
	newSearchTree.m_root = _clone(tempTree.root());
	return newSearchTree;
}

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
	return false;//FIX ME
}

int BinaryTreeSearch::min()const
{
	if (!m_root)
		return INT_MIN;
	Node* root = m_root;
	int min;
	while (root)
	{
		min = root->getKey();
		root = root->getLeft();
	}
	return min;
}

int BinaryTreeSearch::max()const
{
	if (!m_root)
		return INT_MAX;
	Node* root = m_root;
	int max;
	while (root)
	{
		max = root->getKey();
		root = root->getRight();
	}
	return max;
}

std::vector<int> BinaryTreeSearch::treeToVector()const
{
	std::vector<int> keys;
	_treeToVector(m_root, keys);
	return keys;
}

void BinaryTreeSearch::_treeToVector(Node* root, std::vector<int>& keys)const
{
	if (!root)
		return;
	_treeToVector(root->getLeft(), keys);
	keys.push_back(root->getKey());
	_treeToVector(root->getRight(), keys);
}

int BinaryTreeSearch::level(Node* root, const int key, int currentLevel)const
{
	if (!root)
		return -1;
	if (root->getKey() == key)
		return currentLevel;
	if (key < root->getKey())
	{
		return level(root->getLeft(), key, currentLevel + 1);
	}
	else
	{
		return level(root->getRight(), key, currentLevel + 1);
	}
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
