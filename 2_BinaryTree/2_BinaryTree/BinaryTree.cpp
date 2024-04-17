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

void BinaryTree::clearChildren(Node *root)
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
    clearChildren(m_root);
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
        if(tmp.front())
        {
            current = tmp.front();
            if(current->getLeft()){
            nodeList.push_back(current->getLeft());
            tmp.push_back(current->getLeft());
            }
            if(current->getRight()){
            nodeList.push_back(current->getRight());
            tmp.push_back(current->getRight());
            }
        }
        tmp.pop_front();
    }
}

bool BinaryTree::isBalanced() const
{
    return isBalanced(m_root);
}

bool BinaryTree::isBalanced(Node* root) const
{
    if (!root)
        return true;
    int left = height(root->getLeft());
    int right = height(root->getRight());
    int difference = right - left;
    bool balanced = (difference <= 1 && difference >= -1);
    return balanced && isBalanced(root->getLeft()) && isBalanced(root->getRight());
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
        Node* node = find(root->getLeft(), key);
        if (!node)
            node = find(root->getRight(), key);
        return node;
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

BinaryTree::Node* BinaryTree::add(const int key)
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
    if (!removableNode)
        return false;
    Node* replacementNode = nullptr;
    Node* parentNode = nullptr;
    Node* parentReplacementNode = nullptr;
    if (removableNode == m_root)
    {
        if (!removableNode->getLeft() && !removableNode->getRight())
        {
            delete m_root;
            m_root = nullptr;
            return true;
        }
        replacementNode = listTree.back();
        parentNode = parent(replacementNode);
        removableNode->setKey(replacementNode->getKey());
        if (parentNode->getLeft() == replacementNode)
            parentNode->setLeft(nullptr);
        else if(parentNode->getRight() == replacementNode)
            parentNode->setRight(nullptr);
        delete replacementNode;
        return true;
    }
    else if (!removableNode->getLeft() && !removableNode->getRight())//no childs
    {
        parentNode = parent(removableNode);
        if (parentNode->getLeft() == removableNode)
            parentNode->setLeft(nullptr);
        else if (parentNode->getRight() == removableNode)
            parentNode->setRight(nullptr);
        delete removableNode;
        return true;
    }
    else if (removableNode->getLeft() && removableNode->getRight())
    {
        parentNode = parent(removableNode);
        std::vector<Node*> vecLeafs = _leafs(removableNode);
        replacementNode = vecLeafs.back();
        parentReplacementNode = parent(replacementNode);
        if (replacementNode != removableNode->getLeft())
            replacementNode->setLeft(removableNode->getLeft());
        if (replacementNode != removableNode->getRight())
            replacementNode->setRight(removableNode->getRight());
        if (parentReplacementNode->getLeft() == replacementNode)
            parentReplacementNode->setLeft(nullptr);
        else
            parentReplacementNode->setRight(nullptr);
        if (parentNode->getLeft() == removableNode)
            parentNode->setLeft(replacementNode);
        else if (parentNode->getRight() == removableNode)
            parentNode->setRight(replacementNode);
        delete removableNode;
        return true;
    }
    else
    {
        parentNode = parent(removableNode);
        if (removableNode->getLeft())
        {
            replacementNode = removableNode->getLeft();
        }
        else if(removableNode->getRight())
        {
            replacementNode = removableNode->getRight();
        }
        if (parentNode->getLeft() == removableNode)
            parentNode->setLeft(replacementNode);
        else if (parentNode->getRight() == removableNode)
            parentNode->setRight(replacementNode);
        delete removableNode;
        return true;
    }
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

std::vector<BinaryTree::Node*> BinaryTree::_leafs(Node* root) const
{
    std::list<Node*> nodeList;
    std::vector<Node*> leafs;
    nodeList.push_back(root);
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
    std::vector<int> vec;
    if (!m_root)
        return vec;
    nodeList.push_back(m_root);
    _treeToList(nodeList);
    while (!nodeList.empty())
    {
        vec.push_back(nodeList.front()->getKey());
        nodeList.pop_front();
    }
    std::sort(begin(vec),end(vec));
    return vec;
}

int BinaryTree::size() const
{
    std::vector<int> vec = treeToVector();
    return vec.size();
}

int BinaryTree::min() const
{
    if (!m_root)
        return INT_MIN;
    std::vector<int> vec = treeToVector();
    return vec[0];
}

int BinaryTree::max() const
{
    if (!m_root)
        return INT_MAX;
    std::vector<int> vec = treeToVector();
    return vec.back();
}

int BinaryTree::level(const int key) const
{
    return level(m_root, key, 1);
}

int BinaryTree::level(Node* root, const int key, int currentLevel) const
{
    if (!root)
        return -1;
    if (root->getKey() == key)
        return currentLevel;
    int downLevel = level(root->getLeft(), key, currentLevel + 1);
    if (downLevel == -1)
        return level(root->getRight(), key, currentLevel + 1);
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

std::vector<int> BinaryTree::LRR()const
{
    std::vector<int> keys;
    _LRR(m_root, keys);
    return keys;
}

void BinaryTree::_LRR(Node* root, std::vector<int> &vec)const
{
    if (!root)
        return;
    _LRR(root->getLeft(), vec);
    vec.push_back(root->getKey());
    _LRR(root->getRight(), vec);
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

