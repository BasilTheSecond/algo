#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <algorithm>

class KnapSack
{
public:
	class Value
	{
	public:
		Value();
		Value(std::pair<int, int>& parent, double value);
		~Value();

	public:
		std::pair<int, int> m_parent;
		double m_value;
	};

	class Item
	{
	public:
		Item(std::string& description, double value, int size);
		~Item();

	public:
		std::string m_description;
		double m_value;
		int m_size;
	};

public:
	KnapSack(std::vector<Item>& items, int size);
	~KnapSack();
	const std::vector<Item>& mGetResult();
	int mGetCapacity();
	const std::vector<Item>& mGetItems();
	double mGetTotalValue();

private:
	std::map<std::pair<int, int>, Value> m_values;
	std::vector<Item> m_items;
	int m_capacity;
	std::vector<Item> m_result;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<KnapSack::Item> items1;
	items1.push_back(KnapSack::Item(std::string("gold watch"), 10, 3));
	items1.push_back(KnapSack::Item(std::string("box of matches"), 1, 5));
	items1.push_back(KnapSack::Item(std::string("sandwich"), 4, 4));
	KnapSack knapSack1(items1, 5);
	std::cout << "Capacity: " << knapSack1.mGetCapacity() << std::endl;
	const std::vector<KnapSack::Item>& knapSackItems1 = knapSack1.mGetItems();
	std::cout << "All items:" << std::endl;
	for (KnapSack::Item i : knapSackItems1)
	{
		std::cout << i.m_description << " (size: " << i.m_size << ", value: " << i.m_value << ")" << std::endl;
	}
	std::cout << "Contents:" << std::endl;
	const std::vector<KnapSack::Item>& result1 = knapSack1.mGetResult();
	for (KnapSack::Item i : result1)
	{
		std::cout << i.m_description << " (size: " << i.m_size << ", value: " << i.m_value << ")" << std::endl;
	}
	std::cout << "Total value: " << knapSack1.mGetTotalValue() << std::endl;
	std::vector<KnapSack::Item> items2;
	items2.push_back(KnapSack::Item(std::string("golden statue"), 10, 4));
	items2.push_back(KnapSack::Item(std::string("crystal ball"), 4, 2));
	items2.push_back(KnapSack::Item(std::string("fountain pen"), 7,  3));
	KnapSack knapSack2(items2, 5);
	std::cout << "Capacity: " << knapSack2.mGetCapacity() << std::endl;
	const std::vector<KnapSack::Item>& knapSackItems2 = knapSack2.mGetItems();
	std::cout << "All items:" << std::endl;
	for (KnapSack::Item i : knapSackItems2)
	{
		std::cout << i.m_description << " (size: " << i.m_size << ", value: " << i.m_value << ")" << std::endl;
	}
	std::cout << "Contents:" << std::endl;
	const std::vector<KnapSack::Item>& result2 = knapSack2.mGetResult();
	for (KnapSack::Item i : result2)
	{
		std::cout << i.m_description << " (size: " << i.m_size << ", value: " << i.m_value << ")" << std::endl;
	}
	std::cout << "Total value: " << knapSack2.mGetTotalValue() << std::endl;
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

KnapSack::KnapSack(std::vector<Item>& items, int capacity) :
m_items(items),
m_capacity(capacity)
{
	for (int j = 0; j <= m_capacity; j++)
	{
		m_values[std::pair<int, int>(m_items.size() - 1, j)] = Value(std::pair<int, int>(-1, -1), j < m_items[m_items.size() - 1].m_size ? 0 : m_items[m_items.size() - 1].m_value);
	}
	for (int i = m_items.size() - 2; i >= 0; i--)
	{
		for (int j = 0; j <= m_capacity; j++)
		{
			std::vector<Value> values;
			if (j - m_items[i].m_size >= 0)
			{
				values.push_back(Value(std::pair<int, int>(i + 1, j - m_items[i].m_size), m_values[std::pair<int, int>(i + 1, j - m_items[i].m_size)].m_value + m_items[i].m_value));
			}
			values.push_back(Value(std::pair<int, int>(i + 1, j), m_values[std::pair<int, int>(i + 1, j)].m_value));
			std::sort(values.begin(), values.end(), 
								([](Value& a, Value& b)
								{
									return a.m_value >= b.m_value;
								}));
			m_values[std::pair<int, int>(i, j)] = values[0];
		}
	}
	m_result.clear();
	for (std::pair<int, int> current = std::pair<int, int>(0, m_capacity); true; current = m_values[current].m_parent)
	{
		if (m_values[current].m_parent == std::pair<int, int>(-1, -1))
		{
			if (m_values[current].m_value > 0)
			{
				m_result.push_back(m_items[current.first]);
			}
			break;
		}
		if (m_values[current].m_value > m_values[m_values[current].m_parent].m_value)
		{
			m_result.push_back(m_items[current.first]);
		}
	}
}

KnapSack::~KnapSack()
{
}

const std::vector<KnapSack::Item>& KnapSack::mGetResult()
{
	return m_result;
}

int KnapSack::mGetCapacity()
{
	return m_capacity;
}

const std::vector<KnapSack::Item>& KnapSack::mGetItems()
{
	return m_items;
}

double KnapSack::mGetTotalValue()
{
	return m_values[std::pair<int, int>(0, m_capacity)].m_value;
}

KnapSack::Value::Value()
{
}

KnapSack::Value::Value(std::pair<int, int>& parent, double value) :
m_parent(parent),
m_value(value)
{
}

KnapSack::Value::~Value()
{
}

KnapSack::Item::Item(std::string& description, double value, int size) :
m_description(description),
m_value(value),
m_size(size)
{
}

KnapSack::Item::~Item()
{
}
