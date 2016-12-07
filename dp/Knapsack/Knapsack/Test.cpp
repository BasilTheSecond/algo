#include "stdafx.h"
#include <iostream>
#include <map>
#include <string>

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
		Item(std::string& name);
		~Item();

	public:
		std::string m_name;
	};

public:
	KnapSack();
	~KnapSack();

private:
	std::map<std::pair<int, int>, Value> m_values;
};

int _tmain(int argc, _TCHAR* argv[])
{
	KnapSack knapSack;
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

KnapSack::KnapSack()
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

KnapSack::Item::Item(std::string& name) :
m_name(name)
{
}

KnapSack::Item::~Item()
{
}
