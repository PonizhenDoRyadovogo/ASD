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
	std::cout << "min = " << foo.min() << "\n";
	std::cout << "max = " << foo.max() << "\n";
	std::cout << "level 30 = " << foo.BinaryTree::level(90);
	/*std::vector<int> keys = foo.treeToVector();
	for (int i : keys)
	{
		std::cout << i << " ";
	}*/
	return 0;
}
