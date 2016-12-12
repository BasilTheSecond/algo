#include "stdafx.h"
#include <vector>
#include <algorithm>

class HG_Fargo
{
public:
	HG_Fargo();
	~HG_Fargo();

private:
	int m_table[5][21]; // 0 - Dale, 1 - JCN, 2 - JCN, 3 - Macroware, 4 - Pear
};

int _tmain(int argc, _TCHAR* argv[])
{
	HG_Fargo hgFargo;
	return 0;
}

HG_Fargo::HG_Fargo()
{
	int costs[5] = { 12, 10, 20, 18, 15 };
	int values[5] = { 39, 13, 26, 47, 45 };
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (i == 0)
			{
				if (j < costs[0])
				{
					m_table[i][j] = 0;
				}
				else
				{
					m_table[i][j] = values[0];
				}
			}
			else if (j - costs[i] >= 0)
			{
				std::vector<std::pair<int, int>> candidates;
				candidates.push_back(std::pair<int, int>(m_table[i - 1][j] + j, 0));
				candidates.push_back(std::pair<int, int>(m_table[i - 1][j - costs[i]] + j - costs[i] + values[i], 1));
				auto lambdaMax = [](std::pair<int, int>& a, std::pair<int, int>& b)
				{
					return a.first < b.first;
				};
				std::vector<std::pair<int, int>>::iterator iteratorCost = std::min_element(candidates.begin(), candidates.end(), lambdaMax);
				m_table[i][j] = iteratorCost->first;
			}
			else
			{
				m_table[i][j] = m_table[i - 1][j] + j;
			}
		}
	}
}

HG_Fargo::~HG_Fargo()
{
}
