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
	foo.printHorizontal();
	return 0;
}