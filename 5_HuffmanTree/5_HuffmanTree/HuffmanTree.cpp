#include <list>
#include <string>
#include <vector>
#include <fstream>
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

void prependToFile(const std::string& originFilename, const int dataToPrepend)
{
	std::ifstream originFile(originFilename, std::ios::binary);
	if (!originFile.is_open()) {
		std::cerr << "Can't open file for read: " << originFilename << std::endl;
		return;
	}
	std::string tmpFilename = "tmp_" + originFilename;
	std::ofstream tmpFile(tmpFilename, std::ios::binary);
	if (!tmpFile.is_open()) {
		std::cerr << "Can't create temporary file: " << tmpFilename << std::endl;
		return;
	}
	tmpFile << dataToPrepend;
	tmpFile << originFile.rdbuf();

	tmpFile.close();
	originFile.close();

	if (remove(originFilename.c_str()))
	{
		std::cerr << "Error delete: " << originFilename << std::endl;
		return;
	}

	if (rename(tmpFilename.c_str(), originFilename.c_str()))
	{
		std::cerr << "Error rename: " << tmpFilename << std::endl;
		return;
	}
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
		std::cerr << "Can't open file for read: " << inputFilename << std::endl;
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
	_createTree();
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
		std::cerr << "Can't open file for read: " << inputFilename << std::endl;
		return -1;
	}
	std::ofstream outputFile(outputFilename);
	if (!outputFile.is_open())
	{
		std::cerr << "Can't open file for write: " << outputFilename << std::endl;
		return -1;
	}

	unsigned char ch;
	BoolVector code(256, 0);
	int pos = 0;
	inputFile >> std::noskipws;
	inputFile >> ch;
	while (!inputFile.eof())
	{
		if (!_encode(ch, code, pos))
		{
			std::cerr<< "The function is called by another tree. Encoding is impossible or incorrect"<< std::endl;
			return 0;
		}
		unsigned char* symb = code.getCells();
 		int i = 0;
		for (; i < (pos / 8); ++i)
		{
			outputFile << symb[i];
		}
		if (pos / 8)
		{
			code = code << i * 8;
			pos = pos % 8;
		}
		inputFile >> ch;
		if (inputFile.eof() && (pos % 8))
		{
			outputFile << symb[0];
		}
	}
	inputFile.close();
	outputFile.close();

	if (pos == 0)
	{
		prependToFile(outputFilename, 0);
	}
	else
	{
		prependToFile(outputFilename, 8 - pos);
	}

	return ((static_cast<float>(countBitsFile(outputFilename) - 8) / static_cast<float>(countBitsFile(inputFilename))) * 100);
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

bool HuffmanTree::decode(const std::string& encodedFilename, const std::string& decodedFilename)
{
	std::ifstream encodeFile(encodedFilename, std::ios::binary);
	if (!encodeFile.is_open())
	{
		std::cerr << "Can't open file for read: " << encodedFilename << std::endl;
		return false;
	}
	std::ofstream decodeFile(decodedFilename, std::ios::binary);
	if (!decodeFile.is_open())
	{
		std::cerr << "Can't open file for write: " << decodedFilename << std::endl;
		return false;
	}
	encodeFile >> std::noskipws;
	unsigned char insignificantBits;
	encodeFile >> insignificantBits;
	unsigned char ch;
	encodeFile >> ch;
	int i = 0;
	BoolVector way(5000, 0);//????????????? 
	while (!encodeFile.eof())
	{
		way.addSymbol(ch, i);
		encodeFile >> ch;
		++i;
	}
	std::cout << way;
	Node* node = m_root;
	int f = (i * 8) - (insignificantBits - '0');
	for (int j = 0; j < f; ++j)
	{
		if (way[j] == true)
		{
			node = node->left();
			if (!node->left() && !node->right())
			{
				for (int k = 0; k < 256; k++)
				{
					if (node->symbols()[k] == true)
					{
						ch = static_cast<unsigned char>(k);
						break;
					}
				}
				decodeFile << ch;
				node = m_root;
			}
		}
		else
		{
			node = node->right();
			if (!node->left() && !node->right())
			{
				for (int k = 0; k < 256; k++)
				{
					if (node->symbols()[k] == true)
					{
						ch = static_cast<unsigned char>(k);
						break;
					}
				}
				decodeFile << ch;
				node = m_root;
			}
		}
	}
	encodeFile.close();
	decodeFile.close();
}

void HuffmanTree::clear(Node* root)
{
	if (!root)
		return;
	clear(root->left());
	clear(root->right());
	delete root;
}

void HuffmanTree::exportTree(const std::string& filename)
{
	if (!m_root)
	{
		std::cerr << "Tree is empty. Can't export" << std::endl;
		return;
	}
	std::ofstream file(filename);
	for (int i = 0; i < m_tab.size(); ++i)
	{
		file << m_tab[i] << " ";
	}
	file.close();
}

void HuffmanTree::importTree(const std::string& filename)
{
	if (m_root)
	{
		clear(m_root);
	}
	std::ifstream file(filename);
	int frequency;
	file >> frequency;
	for (int i = 0; i < 256; ++i)
	{
		m_tab[i] = frequency;
		file >> frequency;
	}
	_createTree();
}

void HuffmanTree::_createTree()
{
	std::list<Node*> nodeList;
	//create list of Node
	for (int i = 0; i < 256; ++i)
	{
		if (m_tab[i] > 0)
		{
			BoolVector symbols(256, 0);
			symbols[i] = true;
			nodeList.push_back(new Node(symbols, m_tab[i]));
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

