#include<fstream>
#include<iostream>
#include<string>

#include"HuffmanTree.h"

int main()
{
	HuffmanTree foo;
	std::string str = "test.txt";
	foo.build(str);
	std::cout << "\n";
	foo.printHorizontal();
	std::string encodeText = "encode.txt";
	std::cout<< "compression ratio = " << foo.encode(str, encodeText);
	
	return 0;
}