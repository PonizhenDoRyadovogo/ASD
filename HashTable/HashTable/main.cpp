#include<string>
#include<iostream>

#include"HashTable.h"

int main()
{
	FirstHashFunction* hash1 = new FirstHashFunction;
	SecondHashFunction* hash2 = new SecondHashFunction;
	HashTable table(hash1, 10);
	std::string str1 = "Hello";
	std::string str2 = "World";
	std::string str3 = "Ahahhaha";
	std::string str4 = "blabla";

	for (int i = 0; i < 150000; ++i) {
		table.insert(i, std::to_string(i));
	}
	table.print();
	std::cout << "============\n";
	table.changeHash(new FirstHashFunction);
	table.print();
	std::cout << "============\n";
	table.changeHash(new SecondHashFunction);
	table.print();
	std::cout << "============\n";
	table.changeHash(new FirstHashFunction);
	table.print();
	std::cout << "============\n";
	return 0;
	table.insert(5, str1);
	table.insert(5, str2);
	table.insert(5, str3);
	table.insert(5, str4);
	table.print();
	std::cout << "============\n";
	table.changeHash(hash2);
	table.print();
	return 0;
}