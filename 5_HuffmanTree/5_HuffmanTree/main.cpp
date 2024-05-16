#include<fstream>
#include<iostream>
#include<string>

#include"HuffmanTree.h"

int main()
{
	HuffmanTree foo;
	std::string str = "Hello World";
	foo.build(str);
	std::cout << "\n";
	foo.printHorizontal();
	return 0;
}