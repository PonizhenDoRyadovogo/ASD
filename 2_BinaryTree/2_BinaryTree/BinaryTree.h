#pragma once
#include <list>
#include <vector>
class BinaryTree
{
public:
	class Node;

public:
	BinaryTree() = default;
	BinaryTree(const BinaryTree& other);
	virtual ~BinaryTree();
	void clearFrom(Node *root);
	void clear();
	BinaryTree clone(Node *root) const;
	BinaryTree clone() const;
	bool isIdeal() const;
	bool isBalanced() const;
	bool isEmpty() const;
	int nodeCount() const;
	int height() const;
	int height(Node* root) const;
	virtual Node* find(const int key) const;
	virtual Node* find(Node* root, const int key) const;
	virtual Node* addNode(const int key);
	virtual bool remove(const int key);
	virtual bool remove(Node* root, const int key);
	virtual Node* parent(const Node* child) const;
	std::vector<Node*> leafs() const;
	std::vector<int> treeToVector()const;
	void printLeafs() const;
	Node* root() const;
	void printHorizontal(int levelSpacing = 4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
	BinaryTree& operator=(const BinaryTree& other);
private:
	BinaryTree::Node* _addNode(Node* root, const int key);
	Node* _clone(Node* root) const;
	Node* _clone() const;
	void _treeToList(std::list<Node*>& nodeList) const;
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
