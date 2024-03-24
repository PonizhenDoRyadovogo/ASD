#include <iostream>
#include"BinaryTree.h"

int main()
{
	BinaryTree foo, goo;
	{
		for (int i = 0; i < 5; ++i)
		{
			foo.addNode(i);
		}
	}
	foo.printHorizontal();
	std::cout << "=======\n";
	bool isDeleted = foo.remove(0);
	foo.printHorizontal();
	return 0;
	goo = foo;
	goo.printHorizontal();
	//foo.clearFrom(foo.find(1));
	//foo.printHorizontal();
	std::cout << "=======\n";
	foo.clone(foo.find(1)).printHorizontal();
	return 0;
	
}