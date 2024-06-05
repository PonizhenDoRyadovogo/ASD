#include<iostream>
#include<assert.h>
#include<utility>

#include "HashTable.h"

int FirstHashFunction::hash(const int key, const int tableSize) const
{
	int h0 = key % tableSize;
	return ((h0 + d) % tableSize);
}

IHashFunction* FirstHashFunction::_clone()
{
	FirstHashFunction* tmp = new FirstHashFunction;
	return tmp;
}

int SecondHashFunction::hash(const int key, const int tableSize) const
{
	return static_cast<int>((key % tableSize) * (-(1 - sqrt(5)) / 2) * tableSize) % tableSize;
}

IHashFunction* SecondHashFunction::_clone()
{
	SecondHashFunction* tmp = new SecondHashFunction;
	return tmp;
}

HashTable::HashTable(IHashFunction* hashFunction, int capacity)
	: m_capacity(capacity)
	, m_hashFunction(hashFunction)
	, m_table(capacity)
{
	for (int i = 0; i < capacity; ++i)
	{
		m_table[i] = new TableElement;
	}
}

HashTable::HashTable(const HashTable& other)
	: m_capacity(other.m_capacity)
	, m_table(other.m_capacity)
{
	m_hashFunction = other.m_hashFunction->_clone();
	HashTable tmp(other.m_hashFunction->_clone(), other.m_capacity);
	for (int i = 0; i < other.m_capacity; ++i)
	{
		tmp.m_table[i]->m_hasValue = other.m_table[i]->m_hasValue;
		tmp.m_table[i]->m_key = other.m_table[i]->m_key;
		tmp.m_table[i]->m_str = other.m_table[i]->m_str;
		tmp.m_table[i]->m_next = other.m_table[i]->m_next ? tmp.m_table[other._findIndex(other.m_table[i]->m_next)] : nullptr;
		tmp.m_table[i]->m_prev = other.m_table[i]->m_prev ? tmp.m_table[other._findIndex(other.m_table[i]->m_prev)] : nullptr;
	}
	std::swap(m_table, tmp.m_table);
}

HashTable::~HashTable()
{ 
	delete m_hashFunction;
	for (int i = 0; i < m_capacity; ++i)
	{
		delete m_table[i];
	}
}

int HashTable::capacity()const
{
	return m_capacity;
}

bool HashTable::insert(const int key, std::string& str)
{
	if (_isFilled())
	{
		return false;
	}

	int index = m_hashFunction->hash(key, m_capacity);
	if (!m_table[index]->m_hasValue)
	{
		m_table[index]->m_key = key;
		m_table[index]->m_hasValue = true;
		m_table[index]->m_str = str;
		return true;
	}
	else
	{
		if (m_table[index]->m_next)
		{
			int i = index;
			TableElement *tmp = m_table[i];
			while (tmp->m_next && i < m_capacity)
			{
				tmp = tmp->m_next;
				i = _findIndex(tmp);
			}
			for (int j = 0; j < m_capacity; ++j)
			{
				if (!m_table[j]->m_hasValue)
				{
					m_table[j]->m_key = key;
					m_table[j]->m_hasValue = true;
					m_table[j]->m_str = str;
					m_table[i]->m_next = &(*m_table[j]);
					m_table[j]->m_prev = &(*m_table[i]);
					return true;
				}
			}
		}
		else
		{
			for (int j = 0; j < m_capacity; ++j)
			{
				if (!m_table[j]->m_hasValue)
				{
					m_table[j]->m_key = key;
					m_table[j]->m_hasValue = true;
					m_table[j]->m_str = str;
					m_table[index]->m_next = &(*m_table[j]);
					m_table[j]->m_prev = &(*m_table[index]);
					return true;
				}
			}
		}
	}
}

bool HashTable::erase(const int key)
{
	if (!contains(key))
	{
		return false;
	}
	int index = m_hashFunction->hash(key, m_capacity);
	if (m_table[index]->m_key == key)
	{
		if (!m_table[index]->m_prev && !m_table[index]->m_next)
		{
			m_table[index]->m_hasValue = false;
			m_table[index]->m_key = 0;
			m_table[index]->m_str = "";
		}
		else if (m_table[index]->m_prev && !m_table[index]->m_next)
		{
			m_table[index]->m_hasValue = false;
			m_table[index]->m_key = 0;
			m_table[index]->m_str = "";
			m_table[index]->m_prev->m_next = nullptr;
			m_table[index]->m_prev = nullptr;
		}
		else if (m_table[index]->m_next)
		{
			TableElement* tmp = m_table[index];
			while (tmp->m_next && tmp->m_hasValue)
			{
				tmp->m_key = tmp->m_next->m_key;
				tmp->m_str = tmp->m_next->m_str;
				tmp = tmp->m_next;
			}
			tmp->m_hasValue = false;
			tmp->m_key = 0;
			tmp->m_str = "";
			tmp->m_prev->m_next = nullptr;
			tmp->m_prev = nullptr;
		}
	}
	else
	{
		TableElement* tmp = m_table[index];
		while (tmp->m_key != key)
		{
			tmp = tmp->m_next;
		}
		while (tmp->m_next && tmp->m_hasValue)
		{
			tmp->m_key = tmp->m_next->m_key;
			tmp->m_str = tmp->m_next->m_str;
			tmp = tmp->m_next;
		}
		tmp->m_hasValue = false;
		tmp->m_key = 0;
		tmp->m_str = "";
		tmp->m_prev->m_next = nullptr;
		tmp->m_prev = nullptr;
	}
	return true;
}

bool HashTable::contains(const int key)
{
	if (find(key) == "")
	{
		return false;
	}
	else
	{
		return true;
	}
}

std::string HashTable::find(const int key) const
{
	int index = m_hashFunction->hash(key, m_capacity);
	if (m_table[index]->m_hasValue)
	{
		if (m_table[index]->m_key == key)
		{
			return m_table[index]->m_str;
		}
		else
		{
			if (m_table[index]->m_next)
			{
				TableElement* tmp = m_table[index];
				while (tmp->m_next)
				{
					tmp = tmp->m_next;
					if (tmp->m_key == key)
					{
						return tmp->m_str;
					}
				}
				return "";
			}
			else
			{
				return "";
			}
		}
	}
	else
	{
		return "";
	}
}

void HashTable::print() const
{
	for (int i = 0; i < m_capacity; ++i)
	{
		if (m_table[i]->m_hasValue)
		{
			std::cout << i << " " << m_table[i]->m_key << " " << m_table[i]->m_str <<"\n";
		}
	}
}

void HashTable::resize(int newSize)
{
	if (m_capacity == newSize)
	{
		return;
	}
	std::vector<std::pair<int, std::string>> vec = _pairFilledValues();
	m_table.resize(newSize);
	for (int i = 0; i < newSize; ++i)
	{
		if (i < m_capacity)
		{
			m_table[i]->m_hasValue = false;
			m_table[i]->m_next = nullptr;
			m_table[i]->m_prev = nullptr;
			m_table[i]->m_key = 0;
			m_table[i]->m_str = "";
		}
		else
		{
			m_table[i] = new TableElement;
		}
	}
	m_capacity = newSize;
	for (int i = 0; i < vec.size(); ++i)
	{
		insert(vec[i].first, vec[i].second);
	}
}

void HashTable::changeHash(IHashFunction* hashFunction)
{
	assert(hashFunction);
	m_hashFunction = hashFunction;
	std::vector<std::pair<int, std::string>> vec = _pairFilledValues();
	for (int i = 0; i < m_capacity; ++i)
	{
		m_table[i]->m_hasValue = false;
		m_table[i]->m_next = nullptr;
		m_table[i]->m_prev = nullptr;
		m_table[i]->m_key = 0;
		m_table[i]->m_str = "";
	}
	for (int i = 0; i < vec.size(); ++i)
	{
		insert(vec[i].first, vec[i].second);
	}

}

int HashTable::_findIndex(TableElement* element) const
{
	for (int i = 0; i < m_capacity; ++i)
	{
		if((m_table[i]->m_key == element->m_key) && (m_table[i]->m_next == element->m_next))
		{
			return i;
		}
	}
}

std::string& HashTable::operator[](const int key)
{
	assert(contains(key));
	int index = m_hashFunction->hash(key, m_capacity);
	if (m_table[index]->m_key == key)
	{
		return m_table[index]->m_str;
	}
	else
	{
		TableElement* tmp = m_table[index];
		while (tmp->m_next)
		{
			tmp = tmp->m_next;
			if (tmp->m_key == key)
			{
				return tmp->m_str;
			}
		}
	}
}

HashTable& HashTable::operator=(const HashTable& other)
{
	m_hashFunction = other.m_hashFunction->_clone();
	if (m_capacity != other.m_capacity)
	{
		m_table.resize(other.m_capacity);
		m_capacity = other.m_capacity;
	}
	HashTable tmp(other);
	std::swap(m_table, tmp.m_table);
	return *this;
}

bool HashTable::_isFilled() const
{
	for (int i = 0; i < m_capacity; ++i)
	{
		if (!m_table[i]->m_hasValue)
		{
			return false;
		}
	}
	return true;
}

std::vector<std::pair<int, std::string>> HashTable::_pairFilledValues()const
{
	std::vector<std::pair<int, std::string>> vec;
	for (int i = 0; i < m_capacity; ++i)
	{
		if (m_table[i]->m_hasValue)
		{
			std::pair<int, std::string> p{ m_table[i]->m_key, m_table[i]->m_str };
			vec.push_back(p);
		}
	}
	return vec;
}