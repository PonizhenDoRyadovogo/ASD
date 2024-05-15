#pragma once
#include<list>
#include<string>
#include <fstream>
#include "C:\STUDY\Repo\932221b\ThirdLab OOP\ThirdLab OOP\BoolVector.h"
#include "C:\STUDY\Repo\932221b\SixthLab OOP\SixthLab OOP\Set.h"

class HuffmanTree
{
public:
	class Node;
public:
	HuffmanTree() = default;
	~HuffmanTree();
	void clear(Node* root);
	void build(std::string& text);
private:
	Node* m_root = nullptr;
};

class HuffmanTree::Node
{
public:
	Node(const BoolVector& symbols, const int frequency, Node* left = nullptr, Node* right = nullptr);
	~Node() = default;
	int frequency()const;
	BoolVector symbols() const;
	Node* left()const;
	Node* right()const;
	void setLeft(Node* left);
	void setRight(Node* right);
private:
	Node* m_left = nullptr;
	Node* m_right = nullptr;
	int m_frequency = 1;
	BoolVector m_symbols;
};