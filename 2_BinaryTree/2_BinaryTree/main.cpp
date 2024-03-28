#include <iostream>
#include <vector>
#include"BinaryTree.h"

int main()
{
	BinaryTree foo, goo;
	{
		for (int i = 0; i < 10; ++i)
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
	std::cout << "\nmin = " << foo.min();
	std::cout << "\nmax = " << foo.max()<<"\n";
	std::cout<<"level 5 = " << foo.level(5);
	if (foo.isBalanced() == true)
		std::cout << "balanced";
	else
		std::cout << "not balanced";
	//foo.printHorizontal();
	return 0;
	goo = foo;
	goo.printHorizontal();
	//foo.clearFrom(foo.find(1));
	//foo.printHorizontal();
	std::cout << "=======\n";
	foo.clone(foo.find(1)).printHorizontal();
	return 0;
	
}