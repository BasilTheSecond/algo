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
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

