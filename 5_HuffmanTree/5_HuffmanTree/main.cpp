#include<fstream>
#include<iostream>
#include<string>

#include"HuffmanTree.h"

void makeFile(std::string name)
{
	std::ofstream originFile(name);
	originFile.close();
}

int main()
{
	std::string name = "test.txt";
	makeFile(name);
	return 0;
}