#pragma once

#include<list>
#include "../../3_BinaryTreeSearch/3_BinaryTreeSearch/BinaryTreeSearch.h"

class BalancedSearchTree : public BinaryTreeSearch
{
public:
	BalancedSearchTree() = default;
	~BalancedSearchTree() override = default;
	int balance(Node* root) const;
	BalancedSearchTree clone() const;
	BalancedSearchTree clone(Node* root) const;
	void balancing(Node*& root);
	bool remove(const int key) override;
	void balancing(std::list<Node*>& list);
private:
	Node* _addNode(Node* root, const int key) override;
	std::list<Node*> _traverseToRemavableNode(const int key) const;
	std::list<Node*> _traverseToReplacementNode(std::list<Node*>& list)const;
protected:
	void _rightTurn(Node*& root);
	void _leftTurn(Node*& root);
	void _doubleTurnLR(Node*& root);
	void _doubleTurnRL(Node*& root);
private:
	bool m_isFixed = false;
	int m_balanceNode = 0;
};

