#include <list>
#include <string>
#include <vector>
#include <fstream>
#include "HuffmanTree.h"

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

	std::ifstream inputFile(inputFilename, std::ios::binary);
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
	std::ifstream inputFile(inputFilename, std::ios::binary);
	if (!inputFile.is_open())
	{
		std::cerr << "Can't open file for read: " << inputFilename << std::endl;
		return -1;
	}
	std::ofstream outputFile(outputFilename, std::ios::binary);
	if (!outputFile.is_open())
	{
		std::cerr << "Can't open file for write: " << outputFilename << std::endl;
		return -1;
	}

	unsigned char ch;
	BoolVector code(256, 0);
	int pos = 0;
	int countCharInput = 0, countCharOut = 0;
	inputFile >> std::noskipws;
	inputFile >> ch;
	++countCharInput;
	while (!inputFile.eof())
	{
		if (!_encode(ch, code, pos))
		{
			std::cerr<< "The function is called by another tree. Encoding is impossible or incorrect"<< std::endl;
			return 0;
		}
		const unsigned char* symb = code.getCells();
 		int i = 0;
		for (; i < (pos / 8); ++i)
		{
			outputFile << symb[i];
			++countCharOut;
		}
		if (pos / 8)
		{
			code = code << i * 8;
			pos = pos % 8;
		}
		inputFile >> ch;
		++countCharInput;
		if (inputFile.eof() && (pos % 8))
		{
			outputFile << symb[0];
			++countCharOut;
		}
	}
	--countCharInput;
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
	return ((static_cast<float>(countCharOut) / static_cast<float>(countCharInput)) * 100);
}

bool HuffmanTree::_encode(const char symbol, BoolVector& code, int& pos)
{
	Node* root = m_root;
	if (!m_root->left() && !m_root->right())
	{
		code[pos] = true;
		++pos;
		return true;
	}

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
	decodeData data;
	data.m_way.addSymbol(ch, 0);
	data.m_insignificnatBits = insignificantBits - '0';
	data.m_node = m_root;
	int countChar = 1;
	if (encodeFile.peek() == EOF)//if there was only one character in the encoded file
	{
		data.m_flagEOF = true;
		while (data.m_pos != 8 - data.m_insignificnatBits)
		{
			_decode(decodeFile, data);
		}
	}
	while (!encodeFile.eof())
	{
		bool isDecode = _decode(decodeFile, data);
		if ((isDecode && (data.m_pos == 8)) || !isDecode)
		{
			encodeFile >> ch;
			data.m_way.addSymbol(ch, 0);
			data.m_pos = 0;
			if (encodeFile.peek() == EOF)
			{
				data.m_flagEOF = true;
				for (;;)
				{
					if (!_decode(decodeFile, data))
					{
						encodeFile.close();
						decodeFile.close();
						std::cerr << "Can't decode!" << std::endl;
						return false;
					}
					if (data.m_pos == 8 - data.m_insignificnatBits)
						break;
				}
			}
		}
	}
	encodeFile.close();
	decodeFile.close();
	return true;
}

bool HuffmanTree::_decode(std::ofstream& ostream, decodeData& data)
{
	unsigned char ch;
	int insignificantBits = 0;
	if (data.m_flagEOF)
	{
		insignificantBits = data.m_insignificnatBits;
	}
	if (!m_root->left() && !m_root->right())
	{
		for (int i = 0; i < 256; ++i)
		{
			if (m_root->symbols()[i] == true)
			{
				ch = static_cast<unsigned char>(i);
				break;
			}
		}
		for (; data.m_pos < 8 - insignificantBits; ++data.m_pos)
		{
			ostream << ch;
		}
		return true;
	}
	for (; data.m_pos < 8 - insignificantBits; ++data.m_pos)
	{
		if (data.m_way[data.m_pos] == true)
		{
			data.m_node = data.m_node->left();
			if (!data.m_node->left() && !data.m_node->right())
			{
				for (int j = 0; j < 256; j++)
				{
					if (data.m_node->symbols()[j] == true)
					{
						ch = static_cast<unsigned char>(j);
						break;
					}
				}
				ostream << ch;
				data.m_node = m_root;
				++data.m_pos;
				return true;
			}
		}
		else
		{
			data.m_node = data.m_node->right();
			if (!data.m_node->left() && !data.m_node->right())
			{
				for (int j = 0; j < 256; j++)
				{
					if (data.m_node->symbols()[j] == true)
					{
						ch = static_cast<unsigned char>(j);
						break;
					}
				}
				ostream << ch;
				data.m_node = m_root;
				++data.m_pos;
				return true;
			}
		}
	}
	return false;
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

