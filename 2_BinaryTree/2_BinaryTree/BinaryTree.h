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
	void clearChildren(Node *root);
	void clear();
	BinaryTree clone(Node *root) const;
	BinaryTree clone() const;
	bool isBalanced() const;
	bool isBalanced(Node* root) const;
	bool isEmpty() const;
	int nodeCount() const;
	int height() const;
	int height(Node* root) const;
	Node* find(const int key) const;
	virtual Node* find(Node* root, const int key) const;
	Node* add(const int key);
	virtual bool remove(const int key);
	virtual Node* parent(const Node* child) const;
	std::vector<Node*> leafs() const;
	virtual std::vector<int> treeToVector()const;
	int size() const;
	virtual int min() const;
	virtual int max() const;
	int level(const int key) const;
	virtual int level(Node* root, const int key, int currentLevel) const;
	void printLeafs() const;
	Node* root() const;
	void printHorizontal(int levelSpacing = 4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
	BinaryTree& operator=(const BinaryTree& other);
	std::vector<int> LRR()const;
protected:
	virtual BinaryTree::Node* _addNode(Node* root, const int key);
	void _treeToList(std::list<Node*>& nodeList) const;
	std::vector<Node*> _leafs(Node* root) const;
	Node* _clone(Node* root) const;
	void _LRR(Node* root, std::vector<int>& keys)const;
private:
	Node* _clone() const;
protected:
	Node* m_root = nullptr;
};

class BinaryTree::Node
{
public:
	Node(int key = 0, Node* left = nullptr, Node* right = nullptr, int balance = 0);
	~Node() = default;

	int getKey() const;
	void setKey(int key);
	Node* getLeft();
	Node* getRight();
	void setLeft(Node* left);
	void setRight(Node* right);

	int balance() const;
	void setBalance(const int balance);

private:
	int m_key = 0;
	Node* m_left = nullptr;
	Node* m_right = nullptr;
	int m_balance = 0;
};

