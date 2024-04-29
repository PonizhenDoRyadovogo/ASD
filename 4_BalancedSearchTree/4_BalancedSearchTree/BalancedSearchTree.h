#pragma once

#include "../../3_BinaryTreeSearch/3_BinaryTreeSearch/BinaryTreeSearch.h"

class BalancedSearchTree : public BinaryTreeSearch
{
public:
	BalancedSearchTree() = default;
	~BalancedSearchTree() override = default;
	int balance(Node* root) const;
	BalancedSearchTree clone() const;
	BalancedSearchTree clone(Node* root) const;
	//void balancing(Node* root);
	//void rightTurn(Node* root);
private:
	//Node* _addNode(Node* root, const int key) override;
private:
	bool m_isFixed = false;
	int m_balanceNode = 0;
};

