#include<assert.h>
#include "BalancedSearchTree.h"

BalancedSearchTree BalancedSearchTree::clone() const
{
	return clone(m_root);
}

BalancedSearchTree BalancedSearchTree::clone(Node* root) const
{
	BinaryTree tempTree = BinaryTree::clone(root);
	BalancedSearchTree newSearchTree;
	newSearchTree.m_root = _clone(tempTree.root());
	return newSearchTree;
}

//BinaryTree::Node* BalancedSearchTree::_addNode(Node* root, const int key)
//{
//	if (!root)
//	{
//		root = new Node(key);
//	}
//	else if (key < root->getKey())
//	{
//		root->setLeft(_addNode(root->getLeft(), key));
//	}
//	else if (key > root->getKey())
//	{
//		root->setRight(_addNode(root->getRight(), key));
//	}
//	return root;
//}

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
			rightTurn(root);
		}
		else
		{
			doubleTurnLR(root);
		}
	}
	else if (currentBalance == 2)
	{
		if (balance(root->getRight()) > -1)
		{
			leftTurn(root);
		}
		else
		{
			doubleTurnRL(root);
		}
	}
}


void BalancedSearchTree::rightTurn(Node*& root)
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

void BalancedSearchTree::leftTurn(Node*& root)
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

void BalancedSearchTree::doubleTurnLR(Node*& root)
{
	Node* bottom = root->getLeft();
	leftTurn(bottom);
	rightTurn(root);
}

void BalancedSearchTree::doubleTurnRL(Node*& root)
{
	Node* bottom = root->getRight();
	rightTurn(bottom);
	leftTurn(root);
}
