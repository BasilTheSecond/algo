//
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

// Example:
// Input:
// 4 3
// 1 2 3

// Output:
// 4

class TheCoinChangeProblem
{
public:
	TheCoinChangeProblem(int n, const std::vector<int>& coins);
	~TheCoinChangeProblem();
	int mGetResult();

private:
	int mDp(int i, int j);

private:
	int m_n;
	std::vector<int> m_coins;
	std::map<std::pair<int, int>, int> m_dp;
	int m_result;
};

//

TheCoinChangeProblem::TheCoinChangeProblem(int n, const std::vector<int>& coins) :
m_n(n),
m_coins(coins),
m_result(0)
{
	std::sort(m_coins.begin(), m_coins.end());
	m_result = mDp(n, 0);
}

//

TheCoinChangeProblem::~TheCoinChangeProblem()
{
}

//

int 
TheCoinChangeProblem::mDp(int i, int j)
{
	if (m_dp.find(std::pair<int, int>(i, j)) == m_dp.end())
	{
		if (i == 0)
		{
			m_dp[std::pair<int, int>(i, j)] = 1;
		}
		else
		{
			m_dp[std::pair<int, int>(i, j)] = 0;
			for (size_t k = j; k < m_coins.size(); k++)
			{
				if (i - m_coins[k] >= 0)
				{
					m_dp[std::pair<int, int>(i, j)] += mDp(i - m_coins[k], k);
				}
			}
		}
	}
	return m_dp[std::pair<int, int>(i, j)];
}

//

int 
TheCoinChangeProblem::mGetResult()
{
	return m_result;
}

//

int 
main()
{
	std::cout << "Test #1" << std::endl;
	int n1 = 4;
	std::vector<int> coins1 = { 1, 2, 3 };
	std::cout << "N=" << n1 << std::endl;
	std::cout << "coins={ ";
	for (int coin : coins1)
	{
		std::cout << coin << ", ";
	}
	std::cout << " }" << std::endl;
	TheCoinChangeProblem theCoinChangeProblem1(n1, coins1);
	std::cout << "result=" << theCoinChangeProblem1.mGetResult() << std::endl;
	std::cout << "Test #2" << std::endl;
	int n2 = 10;
	std::vector<int> coins2 = { 2, 5, 3, 6 };
	std::cout << "N=" << n2 << std::endl;
	std::cout << "coins={ ";
	for (int coin : coins2)
	{
		std::cout << coin << ", ";
	}
	std::cout << " }" << std::endl;
	TheCoinChangeProblem theCoinChangeProblem2(n2, coins2);
	std::cout << "result=" << theCoinChangeProblem2.mGetResult() << std::endl;
	// Input: N=18 M=23
	// C={ 49 9 40 17 46 24 42 26 43 41 35 1 47 28 20 38 2 44 32 22 18 45 25 }
	// Output: 18
	std::cout << "Test #3" << std::endl;
	int n3 = 18;
	std::vector<int> coins3 = { 49, 9, 40, 17, 46, 24, 42, 26, 43, 41, 35, 1, 47, 28, 20, 38, 2, 44, 32, 22, 18, 45, 25 };
	std::cout << "N=" << n3 << std::endl;
	std::cout << "coins={ ";
	for (int coin : coins3)
	{
		std::cout << coin << ", ";
	}
	std::cout << " }" << std::endl;
	TheCoinChangeProblem theCoinChangeProblem3(n3, coins3);
	std::cout << "result=" << theCoinChangeProblem3.mGetResult() << std::endl;
	// Test Case #9 from https://www.hackerrank.com/challenges/coin-change
	// Input: N=250 M=24
	// C={ 41 34 46 9 37 32 42 21 7 13 1 24 3 43 2 23 8 45 19 30 29 18 35 11 }
	// Output: 15685693751
	std::cout << "Test #4" << std::endl;
	int n4 = 250;
	std::vector<int> coins4 = { 41, 34, 46, 9, 37, 32, 42, 21, 7, 13, 1, 24, 3, 43, 2, 23, 8, 45, 19, 30, 29, 18, 35, 11 };
	std::cout << "N=" << n4 << std::endl;
	std::cout << "coins={ ";
	for (int coin : coins4)
	{
		std::cout << coin << ", ";
	}
	std::cout << " }" << std::endl;
	TheCoinChangeProblem theCoinChangeProblem4(n4, coins4);
	std::cout << "result=" << theCoinChangeProblem4.mGetResult() << std::endl;
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

