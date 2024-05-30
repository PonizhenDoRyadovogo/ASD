#include<string>
#include<iostream>

#include"HashTable.h"

int main()
{
	FirstHashFunction* hash1 = new FirstHashFunction;
	HashTable table(hash1, 10);
	table.insert(5);
	table.insert(10);
	table.insert(2);
	table.print();
	if (table.find(20))
	{
		std::cout << "true";
	}
	return 0;
}