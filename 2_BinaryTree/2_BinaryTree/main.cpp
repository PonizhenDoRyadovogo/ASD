#include <iostream>
#include <vector>
#include"BinaryTree.h"

int main()
{
	BinaryTree foo, goo;
	{
		for (int i = 0; i < 20; ++i)
		{
			foo.addNode(i);
		}
	}
	foo.printHorizontal();
	std::cout << "=======\n";
	std::vector<int> vec = foo.treeToVector();
	for (int i : vec)
	{
		std::cout << i<<" ";
	}
	return 0;
	goo = foo;
	goo.printHorizontal();
	//foo.clearFrom(foo.find(1));
	//foo.printHorizontal();
	std::cout << "=======\n";
	foo.clone(foo.find(1)).printHorizontal();
	return 0;
	
}