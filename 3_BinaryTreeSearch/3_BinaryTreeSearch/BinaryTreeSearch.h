#pragma once

#include<vector>
#include "../../2_BinaryTree/2_BinaryTree/BinaryTree.h"


class BinaryTreeSearch : public BinaryTree
{
public:
	BinaryTreeSearch() = default;
	~BinaryTreeSearch() override = default;

	BinaryTreeSearch clone() const;
	BinaryTreeSearch clone(Node* root) const;
	Node* find(Node* root, const int key) const override;
	bool remove(const int key) override;
	int min()const override;
	int max()const override;
	std::vector<int> treeToVector()const override;
	int level(Node* root, const int key, int currentLevel)const override;
	Node* parent(const Node* child)const override;
protected:
	Node* _addNode(Node* root, const int key) override;
	Node* _findReplacementNode(Node* root)const;
private:
	void _treeToVector(Node* root, std::vector<int> &keys)const;
};

