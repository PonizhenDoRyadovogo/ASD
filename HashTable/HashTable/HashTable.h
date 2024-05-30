#pragma once
#include<string>
#include<vector>

class IHashFunction
{
public:
	virtual int hash(const int key, const int tableSize) const = 0;
};

class FirstHashFunction : public IHashFunction
{
public:
	int hash(const int key, const int tableSize) const override;
private:
	const int d = 3;
	// c = 0
};

class HashTable
{
public:
	struct TableElement;
public:
	HashTable() = default;
	HashTable(IHashFunction* hashFunction, int capacity);
	~HashTable();
	void insert(const int key, std::string& str);
	bool erase(const int key);
	bool contains(const int key);
	void print() const;
private:
	int findIndex(TableElement* element) const;
private:
	IHashFunction *m_hashFunction = nullptr;
	std::vector<TableElement*> m_table;
	struct TableElement
	{
		int m_key = 0;
		std::string m_str = "";
		TableElement* m_next = nullptr;
		TableElement* m_prev = nullptr;
		bool m_hasValue = false;
	};
	int m_capacity = 0;
};

