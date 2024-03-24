#include <iostream>
#include"BinaryTree.h"

int main()
{
	BinaryTree foo;
	{
		for (int i = 0; i < 10; ++i)
		{
			foo.addNode(i);
		}
	}
	BinaryTree goo(foo);
	foo.printHorizontal();
	std::cout << "====================\n";
	goo.printHorizontal();
	std::cout << "\ncount = " << goo.nodeCount();
	return 0;
}