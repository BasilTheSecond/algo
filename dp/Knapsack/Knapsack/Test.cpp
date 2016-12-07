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
		~Value();

	public:
		std::pair<int, int> m_parent;
		std::pair<int, int> m_value;
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
}

KnapSack::~KnapSack()
{
}

KnapSack::Value::Value()
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
