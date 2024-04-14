#pragma once

#include "../../2_BinaryTree/2_BinaryTree/BinaryTree.h"


class BinaryTreeSearch : public BinaryTree
{
public:
	BinaryTreeSearch() = default;
	~BinaryTreeSearch() override = default;

	/*BinaryTreeSearch clone() const;
	BinaryTreeSearch clone(Node* root) const;*/
	Node* find(Node* root, const int key) const override;
	bool remove(const int key) override;
protected:
	Node* _addNode(Node* root, const int key) override;
};

