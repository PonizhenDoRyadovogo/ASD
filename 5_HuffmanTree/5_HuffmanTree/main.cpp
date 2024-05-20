#include<fstream>
#include<iostream>
#include<string>

#include"HuffmanTree.h"

int main()
{
	HuffmanTree foo, goo;
	std::string str = "test.txt";
	std::string str2 = "other.txt";
	goo.build(str2);
	foo.build(str);
	std::cout << "\n";
	foo.printHorizontal();
	std::string encodeText = "encode.txt";
	std::cout<< "compression ratio = " << foo.encode(str, encodeText)<<std::endl;
	foo.exportTree("export.txt");
	goo.importTree("export.txt");
	goo.printHorizontal();
	return 0;
}