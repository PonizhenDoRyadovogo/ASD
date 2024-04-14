#include <iostream>
#include <vector>
#include "BinaryTreeSearch.h"

int main()
{
	BinaryTreeSearch foo, goo;
	int arr[8] = { 50, 70, 60, 20, 30, 90, 90, 10 };
	for (int i = 0; i < 8; ++i) {
		foo.BinaryTree::add(arr[i]);
	}
	foo.printHorizontal();
	std::cout << "\n===============\n";
	goo = foo;
	goo.printHorizontal();
	return 0;
}
