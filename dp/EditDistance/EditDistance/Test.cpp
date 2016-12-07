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
	virtual ~EditDistance();
	void mPrintSteps();

protected:
	void mComputeTable();

protected:
	std::string m_x;
	std::string m_y;

private:
	virtual double mInsertionCost(int i, int j) = 0;
	virtual double mDeletionCost(int i, int j) = 0;
	virtual double mSubstitutionCost(int i, int j) = 0;

private:
	class BackTrace
	{
	public:
		BackTrace();
		BackTrace(std::pair<int, int>& parent, double cost, std::string& operation);
		~BackTrace();

	public:
		std::pair<int, int> m_parent;
		double m_cost;
		std::string m_operation;
	};

private:
	std::map<std::pair<int, int>, BackTrace> m_table; // table with back-trace
};

class LevenshteinDistance : public EditDistance
{
public:
	LevenshteinDistance(std::string& x, std::string& y);
	virtual ~LevenshteinDistance();

private:
	virtual double mInsertionCost(int i, int j);
	virtual double mDeletionCost(int i, int j);
	virtual double mSubstitutionCost(int i, int j);
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::string x("#EXECUTION");
	std::string y("#INTENTION");
	LevenshteinDistance levenshteinDistance(x, y);
	std::cout << "Steps:" << std::endl;
	levenshteinDistance.mPrintSteps();
	std::cout << "Press any key to exit" << std::endl;
	getchar();
	return 0;
}

EditDistance::EditDistance(std::string& x, std::string& y) :
	m_x(x),
	m_y(y)
{
}

EditDistance::~EditDistance()
{
}

void EditDistance::mComputeTable()
{
	m_table[std::pair<int, int>(0, 0)] = BackTrace(std::pair<int, int>(-1, -1), mSubstitutionCost(0, 0), std::string("substitute"));
	for (size_t i = 1; i < m_x.size(); i++)
	{
		m_table[std::pair<int, int>(i, 0)] = BackTrace(std::pair<int, int>(i - 1, 0), m_table[std::pair<int, int>(i - 1, 0)].m_cost + mDeletionCost(i, 0), std::string("delete"));
	}
	for (size_t j = 1; j < m_y.size(); j++)
	{
		m_table[std::pair<int, int>(0, j)] = BackTrace(std::pair<int, int>(0, j - 1), m_table[std::pair<int, int>(0, j - 1)].m_cost + mInsertionCost(0, j), std::string("insert"));
	}
	for (size_t i = 1; i < m_x.size(); i++)
	{
		for (size_t j = 1; j < m_y.size(); j++)
		{
			std::vector<BackTrace> costs;
			costs.push_back(BackTrace(std::pair<int, int>(i - 1, j - 1), m_table[std::pair<int, int>(i - 1, j - 1)].m_cost + mSubstitutionCost(i, j), std::string("substitute")));
			costs.push_back(BackTrace(std::pair<int, int>(i - 1, j), m_table[std::pair<int, int>(i - 1, j)].m_cost + mDeletionCost(i, j), std::string("delete")));
			costs.push_back(BackTrace(std::pair<int, int>(i, j - 1), m_table[std::pair<int, int>(i, j - 1)].m_cost + mInsertionCost(i, j), std::string("insert")));
			std::sort(costs.begin(),
								costs.end(),
								[](BackTrace& a, BackTrace& b)
								{
									return a.m_cost != b.m_cost ? a.m_cost < b.m_cost : a.m_cost < b.m_cost;
								});
			m_table[std::pair<int, int>(i, j)] = costs[0];
		}
	}
}

void EditDistance::mPrintSteps()
{
	BackTrace root = m_table[std::pair<int, int>(m_x.size() - 1, m_y.size() - 1)];
	std::cout << "(" << (m_x.size() - 1) << "," << (m_y.size() - 1) << "): ";
	std::cout << m_x << "-" << std::endl;
	for (BackTrace next = root; true; next = m_table[std::pair<int, int>(next.m_parent)])
	{
		std::cout << "(" << next.m_parent.first << "," << next.m_parent.second << "): ";
		std::cout << m_x.substr(0, next.m_parent.first + 1) << "-" << m_y.substr(next.m_parent.second + 1) << " " << next.m_operation << "(" << next.m_cost << ")" << std::endl;
		if (next.m_parent == std::pair<int, int>(0, 0))
		{
			std::cout << "(" << m_table[next.m_parent].m_parent.first << "," << m_table[next.m_parent].m_parent.second << "): ";
			std::cout << "-" << m_y << " " << m_table[next.m_parent].m_operation << "(" << m_table[next.m_parent].m_cost << ")" << std::endl;
			break;
		}
	}
}

EditDistance::BackTrace::BackTrace(std::pair<int, int>& parent, double cost, std::string& operation) :
	m_parent(parent),
	m_cost(cost),
	m_operation(operation)
{
}

EditDistance::BackTrace::BackTrace()
{
}

EditDistance::BackTrace::~BackTrace()
{
}

LevenshteinDistance::LevenshteinDistance(std::string& x, std::string& y) :
	EditDistance(x, y)
{
	mComputeTable();
}

LevenshteinDistance::~LevenshteinDistance()
{
}

double LevenshteinDistance::mInsertionCost(int i, int j)
{
	return 1;
}

double LevenshteinDistance::mDeletionCost(int i, int j)
{
	return 1;
}
double LevenshteinDistance::mSubstitutionCost(int i, int j)
{
	return (m_x[i] == m_y[j]) ? 0 : 2;
}
