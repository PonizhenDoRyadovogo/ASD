#pragma once
#include "..\..\3_BinaryTreeSearch\3_BinaryTreeSearch\SearchTreeTester.h"

class BalancedSearchTreeTester : public SearchTreeTester
{
public:
	BalancedSearchTreeTester(const bool useConsoleOutput, const bool enableAllTests = true);
	~BalancedSearchTreeTester() override = default;
protected:
    BinaryTree* allocateTree()override;
    void check_addAndCount(const BinaryTree* tree, const int size)override;
    void check_remove(BinaryTree* tree, const int key, const bool result, const int size)override;
    void check_clear(const BinaryTree* tree, const int size)override;
    void check_assign(const BinaryTree* first, const BinaryTree* second)override;
    void assign() override;
};

