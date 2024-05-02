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
			root->decrementBalance();
			balancing(root);
		}
	}
	else if (key > root->getKey())
	{
		root->setRight(_addNode(root->getRight(), key));
		if (!m_isFixed)
		{
			root->incrementBalance();
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
	int currentBalance = root->balance();
	if (currentBalance == 0)
	{
		m_isFixed = true;
	}
	else if (currentBalance == -2)
	{
		if (root->getLeft()->balance() < 1)
		{
			_rightTurn(root);
			balancing(root);
		}
		else
		{
			_doubleTurnLR(root);
			balancing(root);
		}
	}
	else if (currentBalance == 2)
	{
		if (root->getRight()->balance() > -1)
		{
			_leftTurn(root);
			balancing(root);
		}
		else
		{
			_doubleTurnRL(root);
			balancing(root);
		}
	}
}

bool BalancedSearchTree::remove(const int key) 
{
	if (!_traverseToRemavableNode(key))//a node with a key equal to the key is not in the tree
		return false;
	Node* removableNode = m_info.back().root;
	_traverseToReplacementNode();
	auto iteratorRemovableNode = m_info.begin();
	for (; iteratorRemovableNode->root != removableNode; ++iteratorRemovableNode);
	auto iteratorReplacementNode = --m_info.end();
	iteratorReplacementNode->child = iteratorRemovableNode->child;
	iteratorReplacementNode->root->setBalance(iteratorRemovableNode->root->balance());
	std::swap(*iteratorRemovableNode, *iteratorReplacementNode);
	BinaryTreeSearch::remove(key);
	m_info.pop_back();
	m_isFixed = false;
	balancing();
	return true;

	//std::list<Node*> traverseToReplacement;
	//traverseToReplacement = _traverseToRemavableNode(key);
	//if (traverseToReplacement.empty())//a node with a key equal to the key is not in the tree
	//	return false;
	//Node* removableNode = traverseToReplacement.back();
	//traverseToReplacement = _traverseToReplacementNode(traverseToReplacement);
	//auto iteratorRemovableNode = traverseToReplacement.begin();
	//for (; *iteratorRemovableNode != removableNode; ++iteratorRemovableNode);
	//auto iteratorReplacementNode = --traverseToReplacement.end();
	//std::swap(*iteratorRemovableNode, *iteratorReplacementNode);
	//BinaryTreeSearch::remove(key);
	//traverseToReplacement.pop_back();
	//balancing(traverseToReplacement);
	//return true;
}

void BalancedSearchTree::_rightTurn(Node*& root)
{
	assert(root->getLeft());
	Node* bottom = root->getLeft();
	Node* top = BinaryTreeSearch::parent(root);
	root->setLeft(bottom->getRight());
	bottom->setRight(root);
	
	//root->setBalance(root->balance() + 1 + std::max(0, -bottom->balance()));
	//bottom->setBalance(bottom->balance() + 1 + std::max(0, root->balance()));

	if ((bottom->balance() == -1 || bottom->balance() == 0) && root->balance() != -1)
	{
		root->setBalance(0);
		bottom->setBalance(0);
	}
	else if(bottom->balance() == 0 && root->balance() == -1)
	{
		root->setBalance(0);
		bottom->setBalance(1);
	}
	else if (bottom->balance() == -1 && root->balance() == -1)
	{
		bottom->setBalance(1);
		root->setBalance(1);
	}
	else if (bottom->balance() == -2 && root->balance() == -2)
	{
		bottom->setBalance(0);
		root->setBalance(1);
	}
	else if (bottom->balance() == 1 && root->balance() == -1)
	{
		root->setBalance(0);
		bottom->setBalance(2);
	}
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
	if (bottom->balance() == 1 && root->balance() == 2)
	{
		root->setBalance(0);
		bottom->setBalance(0);
	}
	else if (bottom->balance() == 0 && root->balance() == 2)
	{
		root->setBalance(1);
		bottom->setBalance(-1);
	}
	else if (bottom->balance() == 1 && root->balance() == 1)
	{
		root->setBalance(-1);
		bottom->setBalance(-1);
	}
	else if (bottom->balance() == -1 && root->balance() == 1)
	{
		root->setBalance(0);
		bottom->setBalance(-2);
	}
	else if (bottom->balance() == 0 && root->balance() == 1)
	{
		root->setBalance(0);
		bottom->setBalance(-1);
	}
	else if (bottom->balance() == 2 && root->balance() == 2)
	{
		root->setBalance(-1);
		bottom->setBalance(0);
	}
	//bottom->setBalance(bottom->balance() - 1 - std::max(0, -root->balance()));
	//root->setBalance(root->balance() - 1 - std::max(0, bottom->balance()));
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

bool BalancedSearchTree::_traverseToRemavableNode(const int key)
{
	if (m_root->getKey() == key)
	{
		m_info.push_back({ m_root, NoParent });
		return true;
	}
	Node* currentNode = m_root;
	while (currentNode)
	{
		if (currentNode->getKey() == key)
		{
			if (currentNode->getLeft() && currentNode->getRight())
			{
				m_info.push_back({ currentNode, Left });//have 2 child => we go to left
			}
			else if (currentNode->getLeft())
			{
				m_info.push_back({ currentNode, Left });//have one child on left
			}
			else if (currentNode->getRight())
			{
				m_info.push_back({ currentNode, Right });//have one child in right
			}
			else
			{
				m_info.push_back({ currentNode, NoParent });//leaf
			}
			return true;
		}
		else if (currentNode->getKey() > key)
		{
			m_info.push_back({currentNode, Left});
			currentNode = currentNode->getLeft();
		}
		else
		{
			m_info.push_back({ currentNode, Right });
			currentNode = currentNode->getRight();
		}
	}
	m_info.clear();
	return false;
}

bool BalancedSearchTree::_traverseToReplacementNode()
{
	Node* currentNode = m_info.back().root;//removable node
	if (!currentNode->getLeft() && !currentNode->getRight())//removable node is leaf
		return true;
	else if (currentNode->getLeft() && currentNode->getRight())
	{
		currentNode = currentNode->getLeft();
		while (currentNode)
		{
			if (!currentNode->getRight())
			{
				m_info.push_back({ currentNode, NoParent });
				return true;
			}
			else
			{
				m_info.push_back({ currentNode, Right });
				currentNode = currentNode->getRight();
			}
		}
	}
	else if (currentNode->getLeft())
	{
		m_info.push_back({currentNode->getLeft()});
		return true;
	}
	else
	{
		m_info.push_back({ currentNode->getRight() });
		return true;
	}
}

void BalancedSearchTree::balancing()
{
	if (m_info.empty())
		return;
	if (!m_isFixed)
	{
		if (m_info.back().child == Left)
		{
			m_info.back().root->incrementBalance();
		}
		else if (m_info.back().child == Right)
		{
			m_info.back().root->decrementBalance();
		}

		if (m_info.back().root->balance() == 0)
		{
			m_info.pop_back();
			balancing();
		}
		else if (m_info.back().root->balance() == -2)
		{
			if (m_info.back().root->getLeft()->balance() < 1)
			{
				_rightTurn(m_info.back().root);
				if (m_info.back().root == 0)
				{
					m_info.pop_back();
					balancing();
				}
				else
					balancing();
			}
		}
	}


	/*if (list.empty())
		return;
	Node* currentNode = list.back();
	int currentBalance = currentNode->balance();
	if (currentBalance == 0)
	{
		list.pop_back();
		balancing(list);
	}
	else if (currentBalance == -2)
	{
		if (currentNode->getLeft()->balance() < 1)
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
		if (currentNode->getRight()->balance() > -1)
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
	}*/
}