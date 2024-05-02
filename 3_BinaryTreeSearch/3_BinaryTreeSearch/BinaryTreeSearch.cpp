#include "BinaryTreeSearch.h"
#include <stdlib.h>


BinaryTreeSearch BinaryTreeSearch::clone() const
{
	return clone(m_root);
}

BinaryTreeSearch BinaryTreeSearch::clone(Node* root) const
{
	BinaryTreeSearch newSearchTree;
	newSearchTree.m_root = _clone(root);
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
	Node* removableNode = BinaryTree::find(key);
	if (!removableNode)
		return false;
	Node* replacementNode = nullptr;
	Node* parentNode = nullptr;
	Node* parentReplacementNode = nullptr;
	if (!removableNode->getLeft() && !removableNode->getRight())//leaf or root, if tree has one root
	{
		if (removableNode == m_root)
		{
			delete m_root;
			m_root = nullptr;
			return true;
		}
		parentNode = parent(removableNode);
		if (removableNode->getKey() < parentNode->getKey())
		{
			parentNode->setLeft(nullptr);
		}
		else
		{
			parentNode->setRight(nullptr);
		}
		delete removableNode;
		return true;
	}
	else if ((removableNode->getLeft() && !removableNode->getRight()) || 
		(!removableNode->getLeft() && removableNode->getRight()))
	{
		parentNode = parent(removableNode);
		if (removableNode->getLeft())
		{
			replacementNode = removableNode->getLeft();
		}
		else if (removableNode->getRight())
		{
			replacementNode = removableNode->getRight();
		}
		if (parentNode)
		{
			if (removableNode->getKey() < parentNode->getKey())
				parentNode->setLeft(replacementNode);
			else if (removableNode->getKey() > parentNode->getKey())
				parentNode->setRight(replacementNode);
		}
		else//root
			m_root = replacementNode;
		delete removableNode;
		return true;
	}
	else if (removableNode->getLeft() && removableNode->getRight())
	{
		parentNode = parent(removableNode);
		replacementNode = _findReplacementNode(removableNode);
		parentReplacementNode = parent(replacementNode);
		if (!replacementNode->getLeft())//if rp is leaf
		{
			replacementNode->setRight(removableNode->getRight());
			if (parentNode)
			{
				if (parentNode->getLeft() == removableNode)
					parentNode->setLeft(replacementNode);
				else
					parentNode->setRight(replacementNode);
			}
			if (parentReplacementNode != removableNode)
			{
				replacementNode->setLeft(removableNode->getLeft());
				parentReplacementNode->setRight(nullptr);
			}
		}
		else
		{
			replacementNode->setRight(removableNode->getRight());
			if (parentNode)//if no root
			{
				if (parentNode->getLeft() == removableNode)
					parentNode->setLeft(replacementNode);
				else
					parentNode->setRight(replacementNode);
			}
			if (parentReplacementNode != removableNode)
			{
				parentReplacementNode->setRight(replacementNode->getLeft());
				replacementNode->setLeft(removableNode->getLeft());
			}
		}
		if (removableNode == m_root)
			m_root = replacementNode;
		delete removableNode;
		return true;
	}
    return false;
}


/*
* @function min
* @brief find min key in BinaryTreeSearch
* @return value of minimal key in BinaryTreeSearch.
* If tree is empty, returned INT_MIN
*/
int BinaryTreeSearch::min()const
{
    if (!m_root)
    {
        return INT_MIN;
    }
	Node* root = m_root;
	int min;
	while (root)
	{
		min = root->getKey();
		root = root->getLeft();
	}
	return min;
}

/*
* @function max
* @brief find max key in BinaryTreeSearch
* @return value of maximal key in BinaryTreeSearch.
* If tree is empty, returned INT_MAX
*/
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

BinaryTree::Node* BinaryTreeSearch::parent(const Node* child)const
{
	if (m_root == child)
		return nullptr;
	Node* currentRoot = m_root;
	Node* parentNode = m_root;
	int key = child->getKey();
	if (key < currentRoot->getKey())
	{
		currentRoot = currentRoot->getLeft();
	}
	else if (key > currentRoot->getKey())
	{
		currentRoot = currentRoot->getRight();
	}
	while (currentRoot)
	{
		if (currentRoot == child)
			return parentNode;
		else if (key < currentRoot->getKey())
		{
			parentNode = currentRoot;
			currentRoot = currentRoot->getLeft();
		}
		else if (key > currentRoot->getKey())
		{
			parentNode = currentRoot;
			currentRoot = currentRoot->getRight();
		}
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
	else if(key > root->getKey())
	{
		root->setRight(_addNode(root->getRight(), key));
	}
	return root;
}

BinaryTree::Node* BinaryTreeSearch::_findReplacementNode(Node* root)const
{
	Node* tmpRoot = root->getLeft();
	while (tmpRoot)
	{
		if (tmpRoot && !tmpRoot->getRight())
			return tmpRoot;
		tmpRoot = tmpRoot->getRight();
	}
}
