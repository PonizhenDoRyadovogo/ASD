#include <iostream>
#include <vector>
#include "BinaryTreeSearch.h"
#include"SearchTreeTester.h"
int main()
{
	srand(time(0));
	SearchTreeTester tester(false);
	tester.test(1000);
	return 0;

	BinaryTreeSearch foo, goo;
	int arr[8] = { 50, 70, 60, 20, 30, 90, 100, 10 };
	for (int i = 0; i < 8; ++i) {
		foo.BinaryTree::add(arr[i]);
	}
	foo.printHorizontal();
	std::cout << "\n===============\n";
	for (int i = 0; i < 5; ++i)
	{
		foo.remove(arr[i]);
		foo.printHorizontal();
		std::cout << "\n===============\n";
	}
	foo.remove(10);
	foo.printHorizontal();
	return 0;
	std::cout << "min = " << foo.min() << "\n";
	std::cout << "max = " << foo.max() << "\n";
	std::cout << "level 10 = " << foo.BinaryTree::level(10);
	foo.BinaryTree::find(10);
	/*std::vector<int> keys = foo.treeToVector();
	for (int i : keys)
	{
		std::cout << i << " ";
	}*/
	return 0;
}
