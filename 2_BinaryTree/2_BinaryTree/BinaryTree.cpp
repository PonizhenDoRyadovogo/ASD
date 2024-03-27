#include "BinaryTree.h"
#include <assert.h>
#include <string>
#include <vector>
#include <iostream>
#include <list>
#include <stdlib.h>
#include<algorithm>

BinaryTree::BinaryTree(const BinaryTree& other)
{
    m_root = other._clone();
}

BinaryTree::~BinaryTree()
{
    clear();
}

void BinaryTree::clearFrom(Node *root)
{
    if (!root)
        return;
    std::list<Node*> listForClearNode;
    if(root->getLeft())
        listForClearNode.push_back(root->getLeft());
    if (root->getRight())
        listForClearNode.push_back(root->getRight());
    _treeToList(listForClearNode);
    while (!listForClearNode.empty())
    {
        delete listForClearNode.back();
        listForClearNode.pop_back();
    }
    root->setLeft(nullptr);
    root->setRight(nullptr);
}

void BinaryTree::clear()
{
    clearFrom(m_root);
    delete m_root;
    m_root = nullptr;
}

BinaryTree BinaryTree::clone() const
{
    return clone(m_root);
}

BinaryTree BinaryTree::clone(Node* root) const
{
    if (!root)
        return *this;
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

void BinaryTree::_treeToList(std::list<Node*>& nodeList) const
{
    Node* current = nullptr;
    std::list<Node*> tmp;
    tmp = nodeList;
    while (!tmp.empty())
    {
        current = tmp.front();
        tmp.pop_front();
        if (current->getLeft())
        {
            nodeList.push_back(current->getLeft());
            tmp.push_back(current->getLeft());
        }
        if (current->getRight())
        {
            nodeList.push_back(current->getRight());
            tmp.push_back(current->getRight());
        }
    }
}

bool BinaryTree::isIdeal() const
{
    return false;
}

bool BinaryTree::isBalanced() const
{
    return false;
}

bool BinaryTree::isEmpty() const
{
    return m_root == nullptr;
}

int BinaryTree::nodeCount() const
{
    int result = 0;
    if (!m_root)
        return result;
    std::list<Node*> listNode;
    listNode.push_back(m_root);
    _treeToList(listNode);
    result = listNode.size();
    return result;
}

int BinaryTree::height() const
{
    return height(m_root);
}

int BinaryTree::height(Node* root) const
{
    if (!root)
        return 0;
    else
    {
        int leftHeight = height(root->getLeft());
        int rightHeight = height(root->getRight());
        return std::max(leftHeight, rightHeight) + 1;
    }
}

BinaryTree::Node* BinaryTree::find(const int key) const
{
    return find(m_root, key);
}

BinaryTree::Node* BinaryTree::find(Node* root, const int key) const
{
    if (!root)
        return nullptr;

    if (root->getKey() == key)
        return root;
    else
    {
        Node* left = find(root->getLeft(), key);
        Node* right = find(root->getRight(), key);
        if (left)
            return left;
        else if (right)
            return right;
        else
            return nullptr;
    }
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

BinaryTree::Node* BinaryTree::addNode(const int key)
{
    if (m_root) {
        return _addNode(m_root, key);
    }
    else {
        return m_root = new Node(key);
    }
}

bool BinaryTree::remove(const int key)
{
    std::list<Node*> listTree;
    listTree.push_back(m_root);
    _treeToList(listTree);
    Node* removableNode = find(key);
    if (removableNode == m_root)
    {
        Node* replacementNode = listTree.back();
        Node* parentNode = parent(replacementNode);
        removableNode->setKey(replacementNode->getKey());
        clearFrom(parentNode);
        return true;
    }
    return false;
}

bool BinaryTree::remove(Node* root, const int key)
{
    return false;
}

BinaryTree::Node* BinaryTree::parent(const Node* child) const
{
    if (m_root == child)
        return m_root;
    Node* current = nullptr;
    std::list<Node*> nodeList;
    nodeList.push_back(m_root);
    _treeToList(nodeList);
    while (!nodeList.empty())
    {
        current = nodeList.front();
        if (current->getLeft() == child)
        {
            return current;
        }
        else if (current->getRight() == child)
        {
            return current;
        }
        nodeList.pop_front();
    }
    return nullptr;
}

std::vector<BinaryTree::Node*> BinaryTree::leafs() const
{
    std::list<Node*> nodeList;
    std::vector<Node*> leafs;
    nodeList.push_back(m_root);
    _treeToList(nodeList);
    while (!nodeList.empty())
    {
        if (!nodeList.front()->getLeft() && !nodeList.front()->getRight())
        {
            leafs.push_back(nodeList.front());
        }
        nodeList.pop_front();
    }
    return leafs;
}

std::vector<int> BinaryTree::treeToVector()const
{
    std::list<Node*> nodeList;
    nodeList.push_back(m_root);
    _treeToList(nodeList);
    std::vector<int> vec;
    while (!nodeList.empty())
    {
        vec.push_back(nodeList.front()->getKey());
        nodeList.pop_front();
    }
    std::sort(begin(vec),end(vec));
    return vec;
}

void BinaryTree::printLeafs() const
{
    std::vector<Node*> vectorLeafs = leafs();
    for (Node* leafs : vectorLeafs)
    {
        std::cout << leafs->getKey() << " ";
    }
}

BinaryTree::Node* BinaryTree::root() const
{
    return m_root;
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

BinaryTree& BinaryTree::operator=(const BinaryTree& other)
{
    if (m_root == other.m_root)
        return *this;
    clear();
    m_root = other._clone(other.m_root);
    return* this;
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


