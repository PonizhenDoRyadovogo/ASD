#include "BinaryTree.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <stdlib.h>

BinaryTree::BinaryTree(const BinaryTree& other)
{
    m_root = other._clone();
}

BinaryTree::~BinaryTree()
{
    clear();
}

void BinaryTree::clear(Node *root)
{
    if (!root)
        return;
    clear(root->getLeft());
    clear(root->getRight());
    delete root;    
}

void BinaryTree::clear()
{
    clear(m_root);
    m_root = nullptr;
}

BinaryTree BinaryTree::clone() const
{
    return clone(m_root);
}

BinaryTree BinaryTree::clone(Node* root) const
{
    BinaryTree cloneTree;
    cloneTree.m_root = _clone(root);
    return cloneTree;
}

BinaryTree::Node* BinaryTree::_clone() const
{
    return _clone(m_root);
}

BinaryTree::Node* BinaryTree::_clone(Node* root) const
{
    Node* cloneRoot = nullptr;
    if (!root)
        return cloneRoot;
    cloneRoot = new Node(root->getKey());
    cloneRoot->setLeft(_clone(root->getLeft()));
    cloneRoot->setRight(_clone(root->getRight()));
    return cloneRoot;
}

bool BinaryTree::isIdeal() const
{
    return false;
}

bool BinaryTree::isBalanced() const
{
    return false;
}


void BinaryTree::printHorizontal(int levelSpacing) const
{
    printHorizontal(m_root, 0, levelSpacing);
}

void BinaryTree::printHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
    if (root == nullptr) {
        return;
    }

    printHorizontal(root->getRight(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->getKey() << std::endl;
    printHorizontal(root->getLeft(), marginLeft + levelSpacing, levelSpacing);
}

BinaryTree::Node* BinaryTree::addNode(int key)
{
    if (m_root) {
        return _addNode(m_root, key);
    }
    else {
        return m_root = new Node(key);
    }
}

BinaryTree::Node* BinaryTree::_addNode(Node* root, int key)
{
    if (!root) {
        root = new Node(key);
    }
    else if (rand() % 2) {
        root->setLeft(_addNode(root->getLeft(), key));
    }
    else {
        root->setRight(_addNode(root->getRight(), key));
    }

    return root;
}

BinaryTree::Node::Node(int key, Node* left, Node* right)
	: m_key(key)
	, m_left(left)
	, m_right(right)
{
}

int BinaryTree::Node::getKey() const
{
	return m_key;
}	

void BinaryTree::Node::setKey(int key)
{
    m_key = key;
}

BinaryTree::Node* BinaryTree::Node::getLeft()
{
    return m_left;
}

BinaryTree::Node* BinaryTree::Node::getRight()
{
    return m_right;
}

void BinaryTree::Node::setLeft(Node* left)
{
    m_left = left;
}

void BinaryTree::Node::setRight(Node* right)
{
    m_right = right;
}

