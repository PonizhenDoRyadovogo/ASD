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

void HashTable::insert(const int key)
{
	int index = m_hashFunction->hash(key, m_capacity);
	if (!m_table[index]->m_hasValue)
	{
		m_table[index]->m_key = key;
		m_table[index]->m_hasValue = true;
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
					m_table[i]->m_next = &(*m_table[j]);
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
					m_table[index]->m_next = &(*m_table[j]);
				}
			}
		}
	}
}

bool HashTable::erase(const int key)
{
	/*if (!find(key))
	{
		return false;
	}
	int index = m_hashFunction->hash(key, m_capacity);
	if(m_table[index])*/
	return false;
}

bool HashTable::find(const int key)
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
			std::cout << i << " " << m_table[i]->m_key << "\n";
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
