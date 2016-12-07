#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

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

private:
	std::map<std::pair<int, int>, Value> m_values;
	std::vector<Item>& m_items;
	int m_size;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<KnapSack::Item> items;
	items.push_back(KnapSack::Item(std::string("gold watch"), 10, 3));
	items.push_back(KnapSack::Item(std::string("box of matches"), 5, 1));
	items.push_back(KnapSack::Item(std::string("sandwich"), 4, 4));
	KnapSack knapSack(items, 5);
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

KnapSack::KnapSack(std::vector<Item>& items, int size) :
m_items(items),
m_size(size)
{
	for (int j = 0; j <= m_size; j++)
	{
		m_values[std::pair<int, int>(m_items.size() - 1, j)] = Value(std::pair<int, int>(0, 0), j < m_items[m_items.size() - 1].m_size ? 0 : m_items[m_items.size() - 1].m_value);
	}
}

KnapSack::~KnapSack()
{
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
