#pragma once

class BinaryTree
{
public:
	class Node;

public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	~BinaryTree();
	void Clear();
	bool IsIdeal() const;
	bool IsBalanced() const;
	Node* AddNode(int key);
	void PrintHorizontal(int levelSpacing = 4) const;
	void PrintHorizontal(Node* root, int marginLeft, int levelSpacing) const;

private:
	BinaryTree::Node* _AddNode(Node* root, int key);
private:
	Node* m_root = nullptr;
};


class BinaryTree::Node
{
public:
	Node(int key = 0, Node* left = nullptr, Node* right = nullptr);
	~Node() = default;

	
	int GetKey() const;
	void SetKey(int key);

	Node* GetLeft();
	Node* GetRight();
	void SetLeft(Node* left);
	void SetRight(Node* right);
	
private:
	int m_key = 0;
	Node* m_left = nullptr;
	Node* m_right = nullptr;
};
