#include "stdafx.h"
#include <vector>
#include <algorithm>
#include <string>
#include <iostream>

class HG_Fargo
{
public:
	HG_Fargo();
	~HG_Fargo();
	void mPrintResult();

private:
	int m_value[5][21]; // 0 - Dale, 1 - JCN, 2 - JCN, 3 - Macroware, 4 - Pear
	std::pair<int, int> m_parent[5][21];
	std::vector<std::string> m_description;
};

int _tmain(int argc, _TCHAR* argv[])
{
	HG_Fargo hgFargo;
	hgFargo.mPrintResult();
	std::cout << "Press any key to terminate..." << std::endl;
	getchar();
	return 0;
}

HG_Fargo::HG_Fargo()
{
	int costs[5] = { 12, 10, 20, 18, 15 };
	int values[5] = { 39, 13, 26, 47, 45 };
	m_description.push_back(std::string("1 stock of Dale"));
	m_description.push_back(std::string("1 stock of JCN"));
	m_description.push_back(std::string("2 stocks of JCN"));
	m_description.push_back(std::string("1 stock of Macroware"));
	m_description.push_back(std::string("1 stock of Pear"));
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 21; j++)
		{
			if (i == 0)
			{
				if (j < costs[0])
				{
					m_value[i][j] = j;
				}
				else
				{
					m_value[i][j] = j - costs[0] + values[0];
				}
				m_parent[i][j] = std::pair<int, int>(-1, -1);
			}
			else
			{
				if (j - costs[i] >= 0)
				{
					std::vector<std::pair<int, std::pair<int, int>>> candidates;
					candidates.push_back(std::pair<int, std::pair<int, int>>(m_value[i - 1][j], std::pair<int, int>(i - 1, j)));
					candidates.push_back(std::pair<int, std::pair<int, int>>(m_value[i - 1][j - costs[i]] + values[i], std::pair<int, int>(i - 1, j - costs[i])));
					auto lambdaMax = [](std::pair<int, std::pair<int, int>>& a, std::pair<int, std::pair<int, int>>& b)
					{
						return a.first >= b.first;
					};
					std::vector<std::pair<int, std::pair<int, int>>>::iterator iteratorCost = std::min_element(candidates.begin(), candidates.end(), lambdaMax);
					m_value[i][j] = iteratorCost->first;
					m_parent[i][j] = iteratorCost->second;
				}
				else
				{
					m_value[i][j] = m_value[i - 1][j];
					m_parent[i][j] = std::pair<int, int>(i - 1, j);
				}
			}
		}
	}
}

HG_Fargo::~HG_Fargo()
{
}

void HG_Fargo::mPrintResult()
{
	std::vector<std::string> purchases;
	int i = 4;
	int j = 20;
	int value = m_value[i][j];
	std::cout << "(" << i << "," << j << "): " << m_value[i][j] << std::endl;
	for (std::pair<int, int> parent = m_parent[i][j]; parent != std::pair<int, int>(-1, -1); parent = m_parent[parent.first][parent.second])
	{
		if (value > m_value[parent.first][parent.second])
		{
			purchases.push_back(m_description[i]);
		}
		i = parent.first;
		j = parent.second;
		value = m_value[i][j];
		std::cout << "(" << parent.first << "," << parent.second << "): " << value << std::endl;
	}
	for (std::string s : purchases)
	{
		std::cout << s << std::endl;
	}
}
