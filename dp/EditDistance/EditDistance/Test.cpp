#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>

class EditDistance
{
public:
	EditDistance(std::string& x, std::string& y);
	~EditDistance();
	double mInsertionCost(int i, int j);
	double mDeletionCost(int i, int j);
	double mSubstitutionCost(int i, int j);

private:
	std::string m_x;
	std::string m_y;
	std::vector<std::vector<int>> m_table;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::string x("#EXECUTION");
	std::string y("#INTENTION");
	EditDistance editDistance(x, y);
	std::cout << "Press any key to exit" << std::endl;
	getchar();
	return 0;
}

EditDistance::EditDistance(std::string& x, std::string& y) :
	m_x(x),
	m_y(y)
{
	m_table.resize(m_x.size());
	for (size_t i = 0; i < m_table.size(); i++)
	{
		m_table[i].resize(m_y.size());
	}
}

EditDistance::~EditDistance()
{
}

double EditDistance::mInsertionCost(int i, int j)
{
	return 1;
}

double EditDistance::mDeletionCost(int i, int j)
{
	return 1;
}
double EditDistance::mSubstitutionCost(int i, int j)
{
	return (m_x[i] == m_y[j]) ? 0 : 2;
}

