#include "stdafx.h"
#include <iostream>
#include <map>

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
