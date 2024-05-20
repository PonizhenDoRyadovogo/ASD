#pragma once
#include<list>
#include<string>
#include <fstream>
#include<vector>
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
	void build(const std::string& inputFilename);
	float encode(const std::string& inputFilename, const std::string& outputFilename);
	bool decode(const std::string& encodedFilename, const std::string& decodedFilename);
	void printHorizontal(int levelSpacing = 4) const;
	void printHorizontal(Node* root, int marginLeft, int levelSpacing) const;
	void exportTree(const std::string& filename);
	void importTree(const std::string& filename);
private:
	bool _encode(const char symbol, BoolVector& code, int& pos);
	void _createTree();
private:
	Node* m_root = nullptr;
	std::vector<int> m_tab;
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