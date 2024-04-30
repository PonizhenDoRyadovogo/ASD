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
	void balancing(Node*& root);

private:
	Node* _addNode(Node* root, const int key) override;
protected:
	void rightTurn(Node*& root);
	void leftTurn(Node*& root);
	void doubleTurnLR(Node*& root);
	void doubleTurnRL(Node*& root);
private:
	bool m_isFixed = false;
	int m_balanceNode = 0;
};

