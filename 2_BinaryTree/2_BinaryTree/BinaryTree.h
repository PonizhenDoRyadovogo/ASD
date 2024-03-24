#pragma once

class BinaryTree
{
public:
	class Node;

public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	~BinaryTree();
	void clear(Node *root);
	void clear();
	BinaryTree clone(Node *root) const;
	BinaryTree clone() const;
	bool isIdeal() const;
	bool isBalanced() const;
	bool isEmpty() const;
	int nodeCount() const;
	Node* addNode(int key);
	Node* root() const;
	void printHorizontal(int levelSpacing = 4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;

private:
	BinaryTree::Node* _addNode(Node* root, int key);
	Node* _clone(Node* root) const;
	Node* _clone() const;
private:
	Node* m_root = nullptr;
};


class BinaryTree::Node
{
public:
	Node(int key = 0, Node* left = nullptr, Node* right = nullptr);
	~Node() = default;

	
	int getKey() const;
	void setKey(int key);

	Node* getLeft();
	Node* getRight();
	void setLeft(Node* left);
	void setRight(Node* right);
	
private:
	int m_key = 0;
	Node* m_left = nullptr;
	Node* m_right = nullptr;
};
