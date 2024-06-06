#pragma once
#include<string>
#include<vector>
#include<utility>

class IHashFunction
{
public:
	virtual int hash(const int key, const int tableSize) const = 0;
	virtual IHashFunction* _clone() = 0;
};

class FirstHashFunction : public IHashFunction
{
public:
	int hash(const int key, const int tableSize) const override;
	IHashFunction* _clone() override;
private:
	const int d = 3;
	// c = 0
};

class SecondHashFunction : public IHashFunction
{
public:
	int hash(const int key, const int tableSize) const override;
	IHashFunction* _clone() override;
};

class HashTable
{
private:
	struct TableElement;
public:
	HashTable();
	HashTable(IHashFunction* hashFunction, int capacity);
	HashTable(const HashTable& other);
	~HashTable();
	int capacity()const;
	bool insert(const int key, const std::string& str);
	bool erase(const int key);
	bool contains(const int key);
	void print() const;
	void resize(int newSize);
	void changeHash(IHashFunction* hashFunction);
	TableElement* _findElement(const int key) const;
	std::string& operator[](const int key);
	HashTable& operator=(const HashTable& other);
private:
	int _findIndex(TableElement* element) const;
	bool _isFilled() const;
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

