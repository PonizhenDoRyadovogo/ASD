#include<iostream>
#include<assert.h>
#include "BalancedSearchTree.h"
#include"BalancedSearchTreeTester.h"

int main()
{
	srand(time(0));
	BalancedSearchTreeTester tester(false);
	tester.test(1000);
	return 0;

	BalancedSearchTree foo;
	//foo.BinaryTree::add(10);
	//foo.BinaryTree::add(6);
	//foo.BinaryTree::add(16);
	//foo.BinaryTree::add(2);
	////foo.BinaryTree::add(20);
	//foo.BinaryTree::add(14);
	//foo.BinaryTree::add(8);
	///*foo.BinaryTree::add(1);
	//foo.BinaryTree::add(12);*/
	//foo.BinaryTree::add(4);
	///*foo.BinaryTree::add(18);
	//foo.BinaryTree::add(25);*/
	//foo.printHorizontal();
	//std::cout << "=============\n";
	//foo.remove(8);
	//foo.printHorizontal();
	for (int i = 1; i < 30; ++i)
	{
		foo.add(i);
		foo.printHorizontal();
		if (foo.isBalanced())
			std::cout << "\ntrue\n";
		std::cout << "=============\n";
	}
	foo.printHorizontal();
	std::cout << "=============\n";
	for (int i = 0; i < 20; ++i)
	{
		foo.remove(i);
		//foo.printHorizontal();
		if (foo.isBalanced())
			std::cout << "\n true\n";
		std::cout << "=============\n";
	}
	return 0;
}

