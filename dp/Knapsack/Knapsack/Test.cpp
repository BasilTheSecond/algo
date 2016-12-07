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
		Item(std::string& description);
		~Item();

	public:
		std::string m_description;
	};

public:
	KnapSack(std::vector<Item>& items);
	~KnapSack();

private:
	std::map<std::pair<int, int>, Value> m_values;
	std::vector<Item>& m_items;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<KnapSack::Item> items;
	items.push_back(KnapSack::Item(std::string("gold watch")));
	items.push_back(KnapSack::Item(std::string("box of matches")));
	items.push_back(KnapSack::Item(std::string("sandwich")));
	KnapSack knapSack(items);
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

KnapSack::KnapSack(std::vector<Item>& items) :
m_items(items)
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

KnapSack::Item::Item(std::string& description) :
m_description(description)
{
}

KnapSack::Item::~Item()
{
}
