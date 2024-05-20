#include<list>
#include<string>
#include<vector>
#include "HuffmanTree.h"

int countBitsFile(std::string fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		return -1;
	}
	unsigned char ch;
	int i = 0;
	file >> ch;
	++i;
	while (!file.eof())
	{
		file >> ch;
		++i;
	}
	return (i * 8);
}

HuffmanTree::~HuffmanTree()
{
	clear(m_root);
	m_root = nullptr;
}

void HuffmanTree::build(const std::string& inputFilename)
{
	if (m_root)
	{
		clear(m_root);
	}

	std::ifstream inputFile(inputFilename);
	if (!inputFile.is_open())
	{
		return;
	}
	std::list<Node*> nodeList;
	std::vector<int> tab(256, 0);
	unsigned char ch;
	inputFile >> std::noskipws;
	inputFile >> ch;
	while (!inputFile.eof())
	{
		tab[ch]++;
		inputFile >> ch;
	}
	inputFile.close();
	m_tab = tab;
	//create list of Node
	for(int i = 0; i < 256; ++i)
	{
		if (tab[i] > 0)
		{
			BoolVector symbols(256, 0);
			symbols[i] = true;
			nodeList.push_back(new Node(symbols, tab[i]));
		}
	}
	//sort list
	for (std::list<Node*>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		for (std::list<Node*>::iterator jt = nodeList.begin(); jt != nodeList.end(); ++jt)
		{
			if ((*it)->frequency() < (*jt)->frequency())
			{
				std::swap(*it, *jt);
			}
		}
	}
	//create tree
	while (nodeList.size() > 1)
	{
		Node* left = nodeList.front();
		nodeList.pop_front();
		Node* right = nodeList.front();
		nodeList.pop_front();
		BoolVector symbols = left->symbols() | right->symbols();
		Node* parent = new Node(symbols, left->frequency() + right->frequency());
		parent->setLeft(left);
		parent->setRight(right);
		std::list<Node*>::iterator it = nodeList.begin();
		for (; it != nodeList.end(); ++it)
		{
			if ((*it)->frequency() == parent->frequency())
			{
				nodeList.insert(it, parent);
				break;
			}
		}
		if (it == nodeList.end())
		{
			nodeList.insert(it, parent);
		}
	}
	m_root = nodeList.front();
}

float HuffmanTree::encode(const std::string& inputFilename, const std::string& outputFilename)
{
	if (!m_root)
	{
		build(inputFilename);
	}
	std::ifstream inputFile(inputFilename);
	if (!inputFile.is_open())
	{
		return -1;
	}
	std::ofstream outputFile(outputFilename);
	if (!outputFile.is_open())
	{
		return -1;
	}

	unsigned char ch;
	BoolVector code(256, 0);
	int pos = 0;
	inputFile >> std::noskipws;
	inputFile >> ch;
	while (!inputFile.eof())
	{
		_encode(ch, code, pos);
		unsigned char* symb = code.getCells();
		for (int i = 0; i < (pos / 8); ++i)
		{
			outputFile << symb[i];
		}
		if (pos / 8)
		{
			code = code << pos;
			pos = pos % 8;
		}
		inputFile >> ch;
	}
	inputFile.close();
	outputFile.close();
	return ((static_cast<float>(countBitsFile(outputFilename)) / static_cast<float>(countBitsFile(inputFilename))) * 100);
}

bool HuffmanTree::_encode(const char symbol, BoolVector& code, int& pos)
{
	Node* root = m_root;
	while (root->left() || root->right())
	{
		if (root->left()->symbols()[symbol] == true)
		{
			root = root->left();
			code[pos] = true;
			++pos;
		}
		else if (root->right()->symbols()[symbol] == true)
		{
			root = root->right();
			code[pos] = false;
			++pos;
		}
		else
		{
			return false;
		}
	}
	return true;
}

void HuffmanTree::clear(Node* root)
{
	if (!root)
		return;
	clear(root->left());
	clear(root->right());
	delete root;
}

HuffmanTree::Node::Node(const BoolVector& symbols, const int frequency, Node* left, Node* right)
	: m_symbols(symbols)
	, m_frequency(frequency)
	, m_left(left)
	, m_right(right)
{
}

int HuffmanTree::Node::frequency() const
{
	return m_frequency;
}

BoolVector HuffmanTree::Node::symbols() const
{
	return m_symbols;
}

HuffmanTree::Node* HuffmanTree::Node::left()const
{
	return m_left;
}

HuffmanTree::Node* HuffmanTree::Node::right()const
{
	return m_right;
}

void HuffmanTree::Node::setLeft(Node* left)
{
	m_left = left;
}

void HuffmanTree::Node::setRight(Node* right)
{
	m_right = right;
}

void HuffmanTree::printHorizontal(int levelSpacing) const
{
	printHorizontal(m_root, 0, levelSpacing);
}

void HuffmanTree::printHorizontal(Node * root, int marginLeft, int levelSpacing) const
{
	if (root == nullptr) {
		return;
	}

	printHorizontal(root->right(), marginLeft + levelSpacing, levelSpacing);
	for (int i = 0; i < 256; ++i)
	{
		if(root->symbols()[i] == true)
			std::cout << std::string(marginLeft, ' ') << static_cast<char>(i) << std::endl;
	}
	printHorizontal(root->left(), marginLeft + levelSpacing, levelSpacing);
}

