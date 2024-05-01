#include <algorithm>
#include <assert.h>
#include <iostream>

#include "BalancedSearchTreeTester.h"
#include"BalancedSearchTree.h"

BalancedSearchTreeTester::BalancedSearchTreeTester(const bool useConsoleOutput, const bool enableAllTests)
	:SearchTreeTester(useConsoleOutput, enableAllTests)
{
}

BinaryTree* BalancedSearchTreeTester::allocateTree()
{
	return new BalancedSearchTree;
}

void BalancedSearchTreeTester::check_addAndCount(const BinaryTree* tree, const int size)
{
	BinaryTreeTester::check_addAndCount(tree, size);
	assert(tree->isBalanced() && isSearchTree(tree));
}

void BalancedSearchTreeTester::check_remove(BinaryTree* tree, const int key, const bool result, const int size)
{
	BinaryTreeTester::check_remove(tree, key, result, size);
	assert(isSearchTree(tree));
    assert(tree->isBalanced());
}

void BalancedSearchTreeTester::check_clear(const BinaryTree* tree, const int size)
{
	BinaryTreeTester::check_clear(tree, size);
	assert(isSearchTree(tree) && tree->isBalanced());
}

void BalancedSearchTreeTester::check_assign(const BinaryTree* first, const BinaryTree* second)
{
	BinaryTreeTester::check_assign(first, second);
	assert(isSearchTree(first) && first->isBalanced());
	assert(isSearchTree(second) && second->isBalanced());
}

void BalancedSearchTreeTester::assign()
{
    if (!assignCheckEnabled()) {
        return;
    }

    BalancedSearchTree tree1;

    std::vector<int> nodeKeys = generateKeys();
    for (int i = 0; i < m_maxSize; ++i) {
        tree1.add(nodeKeys[i]);
    }

    BalancedSearchTree tree2 = tree1;
    check_assign(&tree1, &tree2);

    tree1 = tree1;
    check_assign(&tree1, &tree2);

    tree1 = tree2;
    check_assign(&tree1, &tree2);

    BalancedSearchTree tree3;
    tree1 = tree3;
    check_assign(&tree1, &tree3);

    tree3 = tree2;
    check_assign(&tree2, &tree3);
}