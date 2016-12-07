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
	void mPrintPath();
	void mPrintSteps();
	double mGetDistance();

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
	std::map<std::pair<int, int>, std::pair<std::pair<int, int>, double>> m_table; // table with back-trace
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
	levenshteinDistance.mPrintPath();
	std::cout << "Distance between: " << x << " and " << y << " : " << levenshteinDistance.mGetDistance() << std::endl;
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
	m_table[std::pair<int, int>(0, 0)] = std::pair<std::pair<int, int>, double>(std::pair<int, int>(-1, -1), mSubstitutionCost(0, 0));
	for (size_t i = 1; i < m_x.size(); i++)
	{
		m_table[std::pair<int, int>(i, 0)] = std::pair<std::pair<int, int>, double>(std::pair<int, int>(i - 1, 0), m_table[std::pair<int, int>(i - 1, 0)].second + mDeletionCost(i, 0));
	}
	for (size_t j = 1; j < m_y.size(); j++)
	{
		m_table[std::pair<int, int>(0, j)] = std::pair<std::pair<int, int>, double>(std::pair<int, int>(0, j - 1), m_table[std::pair<int, int>(0, j - 1)].second + mInsertionCost(0, j));
	}
	for (size_t i = 1; i < m_x.size(); i++)
	{
		for (size_t j = 1; j < m_y.size(); j++)
		{
			std::vector<std::pair<std::pair<int, int>, double>> costs;
			costs.push_back(std::pair<std::pair<int, int>, double>(std::pair<int, int>(i - 1, j - 1), m_table[std::pair<int, int>(i - 1, j - 1)].second + mSubstitutionCost(i, j)));
			costs.push_back(std::pair<std::pair<int, int>, double>(std::pair<int, int>(i - 1, j), m_table[std::pair<int, int>(i - 1, j)].second + mDeletionCost(i, j)));
			costs.push_back(std::pair<std::pair<int, int>, double>(std::pair<int, int>(i, j - 1), m_table[std::pair<int, int>(i, j - 1)].second + mInsertionCost(i, j)));
			std::sort(costs.begin(),
				costs.end(),
				[](std::pair<std::pair<int, int>, double>& a, std::pair<std::pair<int, int>, double>& b)
			{
				return a.second != b.second ? a.second < b.second : a.first < b.first;
			});
			m_table[std::pair<int, int>(i, j)] = costs[0];
		}
	}
}

void EditDistance::mPrintPath()
{
	std::pair<std::pair<int, int>, double> root = m_table[std::pair<int, int>(m_x.size() - 1, m_y.size() - 1)];
	std::cout << "(" << m_x.size() - 1 << "," << m_y.size() - 1 << ")";
	std::cout << "->";
	for (std::pair<std::pair<int, int>, double> next = root; true; next = m_table[std::pair<int, int>(next.first.first, next.first.second)])
	{
		std::cout << "(" << next.first.first << "," << next.first.second << ")";
		if (next.first == std::pair<int, int>(0, 0))
		{
			std::cout << std::endl;
			break;
		}
		else
		{
			std::cout << "->";
		}
	}
}

double EditDistance::mGetDistance()
{
	return  m_table[std::pair<int, int>(m_x.size() - 1, m_y.size() - 1)].second;
}

void EditDistance::mPrintSteps()
{
	std::pair<std::pair<int, int>, double> root = m_table[std::pair<int, int>(m_x.size() - 1, m_y.size() - 1)];
	std::cout << "(" << (m_x.size() - 1) << "," << (m_y.size() - 1) << "): ";
	std::cout << m_x << "||" << std::endl;
	for (std::pair<std::pair<int, int>, double> next = root; true; next = m_table[std::pair<int, int>(next.first.first, next.first.second)])
	{
		std::cout << "(" << next.first.first << "," << next.first.second << "): ";
		std::cout << m_x.substr(0, next.first.first + 1) << "||" << m_y.substr(next.first.second + 1) << std::endl;
		if (next.first == std::pair<int, int>(0, 0))
		{
			std::cout << "(" << m_table[std::pair<int, int>(0, 0)].first.first << "," << m_table[std::pair<int, int>(0, 0)].first.second << "): ";
			std::cout << "||" << m_y << std::endl;
			break;
		}
	}
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
