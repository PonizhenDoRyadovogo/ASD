#include<iostream>

#include "HashTable.h"

int FirstHashFunction::hash(const int key, const int tableSize) const
{
	int h0 = key % tableSize;
	return ((h0 + d) % tableSize);
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

HashTable::~HashTable()
{ 
	delete m_hashFunction;
	for (int i = 0; i < m_capacity; ++i)
	{
		delete m_table[i];
	}
}

void HashTable::insert(const int key, std::string& str)
{
	int index = m_hashFunction->hash(key, m_capacity);
	if (!m_table[index]->m_hasValue)
	{
		m_table[index]->m_key = key;
		m_table[index]->m_hasValue = true;
		m_table[index]->m_str = str;
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
				i = findIndex(tmp);
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
					break;
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
					break;
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
	int index = m_hashFunction->hash(key, m_capacity);
	if (m_table[index]->m_hasValue)
	{
		if (m_table[index]->m_key == key)
		{
			return true;
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
						return true;
					}
				}
			}
			else
			{
				return false;
			}
		}
	}
	else
	{
		return false;
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

int HashTable::findIndex(TableElement* element) const
{
	for (int i = 0; i < m_capacity; ++i)
	{
		if((m_table[i]->m_key == element->m_key) && (m_table[i]->m_next == element->m_next))
		{
			return i;
		}
	}
}
