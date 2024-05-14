#include<list>
#include<string>
#include "HuffmanTree.h"

void HuffmanTree::build(std::string& text)
{
	if (m_root)
	{
		clear();
	}
	if (text.empty())
	{
		return;
	}
	std::list<Node*> nodeList;
	nodeList.push_back(new Node(1, text[0]));
	for (int i = 0; i < text.length(); ++i)
	{

	}
}

void HuffmanTree::clear()
{

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