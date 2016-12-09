#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <limits>

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
	class Cost
	{
	public:
		Cost();
		Cost(std::pair<int, int>& parent, double cost, const std::string& operation);
		~Cost();

	public:
		std::pair<int, int> m_parent;
		double m_cost;
		std::string m_operation;
	};

	class Operation
	{
	public:
		Operation();
		Operation(std::pair<int, int>& position, std::string& operation, double cost);
		~Operation();

	public:
		std::pair<int, int> m_position;
		std::string m_operation;
		double m_cost;

	public:
		static const std::string k_delete;
		static const std::string k_insert;
		static const std::string k_substitute;
		static const std::string k_nop;
	};

public:
	EditDistance(std::string& x, std::string& y);
	virtual ~EditDistance();
	void mPrint();
	const std::vector<Operation>& mGetBackTrace();

protected:
	void mComputeTable();
	void mBackTrace();

protected:
	std::string m_x;
	std::string m_y;

private:
	virtual double mInsertionCost(int i, int j) = 0;
	virtual double mDeletionCost(int i, int j) = 0;
	virtual double mSubstitutionCost(int i, int j) = 0;

private:
	std::map<std::pair<int, int>, Cost> m_table; // table with back-trace
	std::vector<Operation> m_backTrace;
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

class LongestCommonSubsequence : public EditDistance
{
public:
	LongestCommonSubsequence(std::string& x, std::string& y);
	virtual ~LongestCommonSubsequence();

private:
	virtual double mInsertionCost(int i, int j);
	virtual double mDeletionCost(int i, int j);
	virtual double mSubstitutionCost(int i, int j);
};

const std::string EditDistance::Operation::k_delete(std::string("delete"));
const std::string EditDistance::Operation::k_insert(std::string("insert"));
const std::string EditDistance::Operation::k_substitute(std::string("substitute"));
const std::string EditDistance::Operation::k_nop(std::string("nop"));

int _tmain(int argc, _TCHAR* argv[])
{
	std::string x0("#hello");
	std::string y0("#soo");
	LevenshteinDistance levenshteinDistance0(x0, y0);
	levenshteinDistance0.mPrint();
	//std::string x1("#EXECUTION");
	//std::string y1("#INTENTION");
	//LevenshteinDistance levenshteinDistance1(x1, y1);
	//std::cout << "Steps:" << std::endl;
	//std::string x2("#HELLO,WORLD");
	//std::string y2("#BLAH,BLAH");
	//LevenshteinDistance levenshteinDistance2(x2, y2);
	//std::cout << "Steps:" << std::endl;
	//std::string x3("#AGGCTATCACCTGACCTCCAGGCCGATGCCC");
	//std::string y3("#TAGCTATCACGACCGCGGTCGATTTGCCCGAC");
	//LevenshteinDistance levenshteinDistance3(x3, y3);
	//std::cout << "Steps:" << std::endl;
	//std::string x4("#HIEROGLYPHOLOGY");
	//std::string y4("#MICHAELANGELO");
	//LongestCommonSubsequence longestCommonSubsequence4(x4, y4);
	//std::cout << "Steps:" << std::endl;
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
	for (int i = 0; i < static_cast<int>(m_x.size()); i++)
	{
		for (int j = 0; j < static_cast<int>(m_y.size()); j++)
		{
			std::vector<Cost> costs;
			Cost minCost;
			if (i - 1 >= 0 && j - 1 >= 0)
			{
				costs.push_back(Cost(std::pair<int, int>(i - 1, j - 1), m_table[std::pair<int, int>(i - 1, j - 1)].m_cost + mSubstitutionCost(i, j), Operation::k_substitute));
				costs.push_back(Cost(std::pair<int, int>(i - 1, j), m_table[std::pair<int, int>(i - 1, j)].m_cost + mDeletionCost(i, j), Operation::k_delete));
				costs.push_back(Cost(std::pair<int, int>(i, j - 1), m_table[std::pair<int, int>(i, j - 1)].m_cost + mInsertionCost(i, j), Operation::k_insert));
				auto lambdaMin = [](Cost& a, Cost& b)
				{
					return a.m_cost < b.m_cost;
				};
				std::vector<Cost>::iterator iteratorCost = std::min_element(costs.begin(), costs.end(), lambdaMin);
				minCost = *iteratorCost;
			}
			else if (i == 0 && j - 1 >= 0)
			{
				minCost = Cost(std::pair<int, int>(i, j - 1), m_table[std::pair<int, int>(i, j - 1)].m_cost + mInsertionCost(i, j), Operation::k_insert);
			}
			else if (i - 1 >= 0 && j == 0)
			{
				minCost = Cost(std::pair<int, int>(i - 1, j), m_table[std::pair<int, int>(i - 1, j)].m_cost + mDeletionCost(i, j), Operation::k_delete);
			}
			else // i == 0 && j == 0
			{
				minCost = Cost(std::pair<int, int>(-1, -1), 0, Operation::k_nop);
			}
			m_table[std::pair<int, int>(i, j)] = minCost;
		}
	}
}

void EditDistance::mBackTrace()
{
	for (std::pair<int, int> position = std::pair<int, int>(m_x.size() - 1, m_y.size() - 1); position != std::pair<int, int>(-1, -1); position = m_table[position].m_parent)
	{
		m_backTrace.push_back(Operation(position, m_table[position].m_operation, m_table[position].m_cost));
	}
}

void EditDistance::mPrint()
{
	std::string x = m_x;
	for (size_t i = 0, k = 0; i < m_backTrace.size(); i++)
	{
		Operation operation = m_backTrace[m_backTrace.size() - 1 - i];
		char cx = m_x.at(operation.m_position.first);
		char cy = m_y.at(operation.m_position.second);
		std::cout << x << " " << operation.m_operation;
		if (operation.m_operation == Operation::k_delete)
		{
			std::cout << " " << cx << " " << "cost: " << operation.m_cost << std::endl;
			x.erase(k, 1);
		}
		else if (operation.m_operation == Operation::k_insert)
		{
			std::cout << " " << cy << " " << "cost: " << operation.m_cost << std::endl;
			x.insert(k, 1, cy);
		}
		else if (operation.m_operation == Operation::k_substitute)
		{
			std::cout << " " << cx << " with " << cy << " " << "cost: " << operation.m_cost << std::endl;
			x.at(k++) = cy;
		}
		else if (operation.m_operation == Operation::k_nop)
		{
			std::cout << " " << "cost: " << operation.m_cost << std::endl;
			k++;
		}
	}
	std::cout << x << std::endl;
}

const std::vector<EditDistance::Operation>& EditDistance::mGetBackTrace()
{
	return m_backTrace;
}

EditDistance::Cost::Cost(std::pair<int, int>& parent, double cost, const std::string& operation) :
m_parent(parent),
m_cost(cost),
m_operation(operation)
{
}

EditDistance::Cost::Cost()
{
}

EditDistance::Cost::~Cost()
{
}

EditDistance::Operation::Operation()
{
}

EditDistance::Operation::Operation(std::pair<int, int>& position, std::string& operation, double cost) :
m_position(position),
m_operation(operation),
m_cost(cost)
{
}

EditDistance::Operation::~Operation()
{
}

LevenshteinDistance::LevenshteinDistance(std::string& x, std::string& y) :
	EditDistance(x, y)
{
	mComputeTable();
	mBackTrace();
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

LongestCommonSubsequence::LongestCommonSubsequence(std::string& x, std::string& y) :
EditDistance(x, y)
{
	mComputeTable();
	mBackTrace();
}

LongestCommonSubsequence::~LongestCommonSubsequence()
{
}

double LongestCommonSubsequence::mInsertionCost(int i, int j)
{
	return 1;
}

double LongestCommonSubsequence::mDeletionCost(int i, int j)
{
	return 1;
}
double LongestCommonSubsequence::mSubstitutionCost(int i, int j)
{
	return (m_x[i] == m_y[j]) ? 0 : std::numeric_limits<double>::max();
}
