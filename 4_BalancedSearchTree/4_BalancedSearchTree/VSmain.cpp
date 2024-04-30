#include<iostream>
#include "BalancedSearchTree.h"

int main()
{
	BalancedSearchTree foo;
	foo.BinaryTree::add(10);
	foo.BinaryTree::add(20);
	foo.BinaryTree::add(40);
	foo.BinaryTree::add(35);
	foo.BinaryTree::add(38);
	foo.BinaryTree::add(36);
	foo.BinaryTree::add(5);
	foo.printHorizontal();
	return 0;
}