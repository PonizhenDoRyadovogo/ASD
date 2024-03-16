#include "BinaryTree.h"
#include <assert.h>
#include <string>
#include <iostream>
#include <stdlib.h>

void BinaryTree::Clear()
{

}

BinaryTree::BinaryTree(const BinaryTree& other)
{
    assert(false && "IMPLEMENT ME PLEASE");
}

BinaryTree::~BinaryTree()
{
    assert(false && "IMPLEMENT ME PLEASE");
}

bool BinaryTree::IsIdeal() const
{
    return false;
}

bool BinaryTree::IsBalanced() const
{
    return false;
}


void BinaryTree::PrintHorizontal(int levelSpacing) const
{
    PrintHorizontal(m_root, 0, levelSpacing);
}

void BinaryTree::PrintHorizontal(Node* root, int marginLeft, int levelSpacing) const
{
    if (root == nullptr) {
        return;
    }

    PrintHorizontal(root->GetRight(), marginLeft + levelSpacing, levelSpacing);
    std::cout << std::string(marginLeft, ' ') << root->GetKey() << std::endl;
    PrintHorizontal(root->GetLeft(), marginLeft + levelSpacing, levelSpacing);
}

BinaryTree::Node* BinaryTree::AddNode(int key)
{
    if (m_root) {
        return _AddNode(m_root, key);
    }
    else {
        return m_root = new Node(key);
    }
}

BinaryTree::Node* BinaryTree::_AddNode(Node* root, int key)
{
    if (!root) {
        root = new Node(key);
    }
    else if (rand() % 2) {
        root->SetLeft(_AddNode(root->GetLeft(), key));
    }
    else {
        root->SetRight(_AddNode(root->GetRight(), key));
    }

    return root;
}

BinaryTree::Node::Node(int key, Node* left, Node* right)
	: m_key(key)
	, m_left(left)
	, m_right(right)
{
}

int BinaryTree::Node::GetKey() const
{
	return m_key;
}	

void BinaryTree::Node::SetKey(int key)
{
    m_key = key;
}

BinaryTree::Node* BinaryTree::Node::GetLeft()
{
    return m_left;
}

BinaryTree::Node* BinaryTree::Node::GetRight()
{
    return m_right;
}

void BinaryTree::Node::SetLeft(Node* left)
{
    m_left = left;
}

void BinaryTree::Node::SetRight(Node* right)
{
    m_right = right;
}

