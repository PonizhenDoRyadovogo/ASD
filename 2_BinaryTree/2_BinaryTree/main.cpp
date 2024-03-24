#include <iostream>
#include"BinaryTree.h"

int main()
{
	BinaryTree foo;
	BinaryTree::Node* node = nullptr;
	{
		for (int i = 0; i < 5; ++i)
		{
			foo.addNode(i);
		}
	}
	foo.printHorizontal();
	node = foo.find(1);
	foo.clearFrom(node);
	foo.printHorizontal();
	return 0;
	BinaryTree goo(foo);
	std::cout << "====================\n";
	goo.printHorizontal();
	std::cout << "\ncount = " << goo.nodeCount();
	std::cout << "\nheight = " << goo.height();
	return 0;
}