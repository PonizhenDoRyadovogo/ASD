#include<assert.h>
#include<list>
#include<algorithm>
#include "BalancedSearchTree.h"

BalancedSearchTree BalancedSearchTree::clone() const
{
	return clone(m_root);
}

BalancedSearchTree BalancedSearchTree::clone(Node* root) const
{
	BalancedSearchTree newSearchTree;
	newSearchTree.m_root = _clone(root);
	return newSearchTree;
}

BinaryTree::Node* BalancedSearchTree::_addNode(Node* root, const int key)
{
	if (!root)
	{
		root = new Node(key);
		m_isFixed = false;
	}
	else if (key < root->getKey())
	{
		root->setLeft(_addNode(root->getLeft(), key));
		if (!m_isFixed)
		{
			balancing(root);
		}
	}
	else if (key > root->getKey())
	{
		root->setRight(_addNode(root->getRight(), key));
		if (!m_isFixed)
		{
			balancing(root);
		}
	}
	return root;
}

int  BalancedSearchTree::balance(Node* root) const
{
	if (!m_root)
		return 0;
	if (root->getRight() && root->getLeft())
	{
		return (height(root->getRight()) - height(root->getLeft()));
	}
	else if (root->getRight())
	{
		return height(root->getRight());
	}
	else 
	{
		return -height(root->getLeft());
	}
	return 0;
}


void BalancedSearchTree::balancing(Node*& root)
{
	int currentBalance = balance(root);
	if (currentBalance == 0)
	{
		m_isFixed = true;
	}
	else if (currentBalance == -2)
	{
		if (balance(root->getLeft()) < 1)
		{
			_rightTurn(root);
		}
		else
		{
			_doubleTurnLR(root);
		}
	}
	else if (currentBalance == 2)
	{
		if (balance(root->getRight()) > -1)
		{
			_leftTurn(root);
		}
		else
		{
			_doubleTurnRL(root);
		}
	}
}

bool BalancedSearchTree::remove(const int key) 
{
	std::list<Node*> traverseToReplacement;
	traverseToReplacement = _traverseToRemavableNode(key);
	if (traverseToReplacement.empty())//a node with a key equal to the key is not in the tree
		return false;
	Node* removableNode = traverseToReplacement.back();
	traverseToReplacement = _traverseToReplacementNode(traverseToReplacement);
	auto iteratorRemovableNode = traverseToReplacement.begin();
	for (; *iteratorRemovableNode != removableNode; ++iteratorRemovableNode);
	auto iteratorReplacementNode = --traverseToReplacement.end();
	std::swap(*iteratorRemovableNode, *iteratorReplacementNode);
	BinaryTreeSearch::remove(key);
	traverseToReplacement.pop_back();
	balancing(traverseToReplacement);
	return true;
}

void BalancedSearchTree::_rightTurn(Node*& root)
{
	assert(root->getLeft());
	Node* bottom = root->getLeft();
	Node* top = BinaryTreeSearch::parent(root);
	root->setLeft(bottom->getRight());
	bottom->setRight(root);
	if (top)
	{
		if (top->getLeft() == root)
		{
			top->setLeft(bottom);
		}
		else
		{
			top->setRight(bottom);
		}
	}
	else//root == m_root
		m_root = bottom;
	root = bottom;
}

void BalancedSearchTree::_leftTurn(Node*& root)
{
	assert(root->getRight());
	Node* bottom = root->getRight();
	Node* top = BinaryTreeSearch::parent(root);
	root->setRight(bottom->getLeft());
	bottom->setLeft(root);
	if (top)
	{
		if (top->getLeft() == root)
		{
			top->setLeft(bottom);
		}
		else
		{
			top->setRight(bottom);
		}
	}
	else//root == m_root
		m_root = bottom;
	root = bottom;
}

void BalancedSearchTree::_doubleTurnLR(Node*& root)
{
	Node* bottom = root->getLeft();
	_leftTurn(bottom);
	_rightTurn(root);
}

void BalancedSearchTree::_doubleTurnRL(Node*& root)
{
	Node* bottom = root->getRight();
	_rightTurn(bottom);
	_leftTurn(root);
}

std::list<BinaryTree::Node*> BalancedSearchTree::_traverseToRemavableNode(const int key) const
{
	std::list<Node*> traverse;
	traverse.push_back(m_root);
	Node* currentNode = m_root;
	while (currentNode)
	{
		if (currentNode->getKey() == key)
			return traverse;
		if (currentNode->getKey() > key)
		{
			currentNode = currentNode->getLeft();
			traverse.push_back(currentNode);
		}
		else
		{
			currentNode = currentNode->getRight();
			traverse.push_back(currentNode);
		}
	}
	traverse.clear();
	return traverse;
}

std::list<BinaryTree::Node*> BalancedSearchTree::_traverseToReplacementNode(std::list<Node*>& list)const
{
	Node* currentNode = list.back();
	if (!currentNode->getLeft() && !currentNode->getRight())//removable node is leaf
		return list;
	else if (currentNode->getLeft() && currentNode->getRight())
	{
		currentNode = currentNode->getLeft();
		list.push_back(currentNode);
		while (currentNode)
		{
			if (!currentNode->getRight())
			{
				return list;
			}
			currentNode = currentNode->getRight();
			list.push_back(currentNode);
		}
	}
	else if (currentNode->getLeft())
	{
		list.push_back(currentNode->getLeft());
		return list;
	}
	else
	{
		list.push_back(currentNode->getRight());
		return list;
	}
}

void BalancedSearchTree::balancing(std::list<Node*>& list)
{
	if (list.empty())
		return;
	Node* currentNode = list.back();
	int currentBalance = balance(currentNode);
	if (currentBalance == 0)
	{
		list.pop_back();
		balancing(list);
	}
	else if (currentBalance == -2)
	{
		if (balance(currentNode->getLeft()) < 1)
		{
			_rightTurn(currentNode);
			list.pop_back();
			balancing(list);
		}
		else
		{
			_doubleTurnLR(currentNode);
			list.pop_back();
			balancing(list);
		}
	}
	else if (currentBalance == 2)
	{
		if (balance(currentNode->getRight()) > -1)
		{
			_leftTurn(currentNode);
			list.pop_back();
			balancing(list);
		}
		else
		{
			_doubleTurnRL(currentNode);
			list.pop_back();
			balancing(list);
		}
	}
}