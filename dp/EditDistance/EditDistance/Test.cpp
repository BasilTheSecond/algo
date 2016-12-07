#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>

// Explanations of insertion, deletion and substitution steps:
// Elements in the edit step table represent x in the various stages of transformation
// towards y. In general:
// x(i, j)	= xorig[0:i-1]	|| x[i] || y[j+1:]
// y				= y[0:j-1]			|| y[j] || y[j+1:]
// NOTE: x(i, j) has prefix 0:i as original x and the rest is suffix y[j+1:]
// If y[j+1:] suffix is aligned with the same suffix in y, then x[i] and y[j] are aligned
// and x string manipulation happens at this point.
// After one of the steps, x(i, j) goes to one of x(i-1, j-1), x(i-1, j) or x(i, j-1)
// 
// 1) Insertion step
// =================
// insert y[j] after x[i]
// x(i, j) -> x(i, j-1)
// Exlanation of the step:
// Before insertion:
// x(i, j)	= xorig[0:i-1]	|| x[i] || y[j+1:]
// y				= y[0:j-1]			|| y[j] || y[j+1:]
// After insertion of y[j] after x[i]
// x = xorig[0:i-1]	|| x[i]		|| y[j] || y[j+1:]
// y = y[0:j-2]			|| y[j-1]	|| y[j] || y[j+1:]
// Therfore:
// x(i, j-1)	= xorig[0:i-1]	|| x[i]		|| y[j:]
// y					= y[0:j-2]			|| y[j-1] || y[j:]
// 2) Deletion step
// =================
// delete x[i]
// x(i, j) -> x(i-1, j)
// Exlanation of the step:
// Before deletion:
// x(i, j)	= xorig[0:i-1]	|| x[i] || y[j+1:]
// y				= y[0:j-1]			|| y[j] || y[j+1:]
// After deleting of x[i]
// x = xorig[0:i-2]	|| x[i-1] || y[j+1:]
// y = y[0:j-1]			|| y[j]		|| y[j+1:]
// Therfore:
// x(i-1, j)	= xorig[0:i-2]	|| x[i-1]	|| y[j+1:]
// y					= y[0:j-1]			|| y[j]		|| y[j+1:]
// 3) Substitution step
// =================
// substitute x[i] with y[j]
// x(i, j) -> x(i-1, j-1)
// Exlanation of the step:
// Before deletion:
// x(i, j)	= xorig[0:i-1]	|| x[i] || y[j+1:]
// y				= y[0:j-1]			|| y[j] || y[j+1:]
// After substituting x[i] with y[j]
// x = xorig[0:i-1]	|| y[j] || y[j+1:]
// y = y[0:j-1]			|| y[j]	|| y[j+1:]
// Therfore:
// x(i-1, j-1)	= xorig[0:i-2]	|| x[i-1]	|| y[j] || y[j+1:]
// y					= y[0:j-2]				|| y[j-1]	|| y[j]	|| y[j+1:]
// x(i-1, j-1)	= xorig[0:i-2]	|| x[i-1]	|| y[j:]
// y					= y[0:j-2]				|| y[j-1]	|| y[j:]

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
	std::vector<std::vector<double>> m_table;
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
	m_table[0][0] = mSubstitutionCost(0, 0);
	for (size_t i = 1; i < m_x.size(); i++)
	{
		m_table[i][0] = m_table[i - 1][0] + mDeletionCost(i, 0);
	}
	for (size_t j = 1; j < m_y.size(); j++)
	{
		m_table[0][j] = m_table[0][j - 1] + mInsertionCost(0, j);
	}
	for (size_t i = 1; i < m_x.size(); i++)
	{
		for (size_t j = 1; j < m_y.size(); j++)
		{
			std::vector<std::pair<std::pair<int, int>, double>> costs;
			costs.push_back(std::pair<std::pair<int, int>, double>(std::pair<int, int>(i - 1, j - 1), m_table[i - 1][j - 1] + mSubstitutionCost(i, j)));
			costs.push_back(std::pair<std::pair<int, int>, double>(std::pair<int, int>(i - 1, j), m_table[i - 1][j] + mDeletionCost(i, j)));
			costs.push_back(std::pair<std::pair<int, int>, double>(std::pair<int, int>(i, j - 1), m_table[i][j - 1] + mInsertionCost(i, j)));
			std::sort(costs.begin(), 
								costs.end(), 
								[](std::pair<std::pair<int, int>, double>& a, std::pair<std::pair<int, int>, double>& b)
								{
									return a.second != b.second ? a.second < b.second : a.first < b.first;
								});
			m_table[i][j] = costs[0].second;
		}
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

