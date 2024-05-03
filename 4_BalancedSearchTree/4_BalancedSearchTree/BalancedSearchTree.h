#pragma once

#include<list>
#include "../../3_BinaryTreeSearch/3_BinaryTreeSearch/BinaryTreeSearch.h"

class BalancedSearchTree : public BinaryTreeSearch
{
public:
	BalancedSearchTree() = default;
	~BalancedSearchTree() override = default;
	BalancedSearchTree clone() const;
	BalancedSearchTree clone(Node* root) const;
	bool remove(const int key) override;
	int balance(Node* root) const;
private:
	Node* _addNode(Node* root, const int key) override;
	bool _traverseToRemavableNode(const int key);
	bool _traverseToReplacementNode();
protected:
	void balancing(Node*& root);
	void balancing();
	void _rightTurn(Node*& root);
	void _leftTurn(Node*& root);
	void _doubleTurnLR(Node*& root);
	void _doubleTurnRL(Node*& root);
private:
	bool m_isFixed = false;

	enum ChildType
	{
		Left = -1,
		NoParent = 0,
		Right = 1
	};
	struct TraverseInfo
	{
		Node* root = nullptr;
		ChildType child = NoParent;

		TraverseInfo(Node* root = nullptr, ChildType child = NoParent)
			: root(root)
			, child(child)
		{}
	};
	std::list<TraverseInfo> m_info;
};

