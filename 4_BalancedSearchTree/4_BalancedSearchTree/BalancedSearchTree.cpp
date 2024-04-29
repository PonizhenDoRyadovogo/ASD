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
//		m_isFixed = false;
//	}
//	else if (key < root->getKey())
//	{
//		root->setLeft(_addNode(root->getLeft(), key));
//		if (!m_isFixed)
//		{
//			m_balanceNode = balance(root) - 1;
//			balancing(root);
//		}
//	}
//	else if (key > root->getKey())
//	{
//		root->setRight(_addNode(root->getRight(), key));
//		if (!m_isFixed)
//		{
//			m_balanceNode = balance(root) + 1;
//			balancing(root);
//		}
//	}
//	return root;
//}

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


//void BalancedSearchTree::balancing(Node* root)
//{
//	if (m_balanceNode == 0)
//	{
//		m_isFixed = true;
//	}
//	else if (m_balanceNode == -2)
//	{
//		if (balance(root->getLeft()) < 1)
//		{
//
//		}
//		else
//		{
//
//		}
//	}
//	else if (m_balanceNode == 2)
//	{
//		if (balance(root->getRight()) > -1)
//		{
//
//		}
//		else
//		{
//
//		}
//	}
//}

//
//void BalancedSearchTree::rightTurn(Node* root)
//{
//
//}