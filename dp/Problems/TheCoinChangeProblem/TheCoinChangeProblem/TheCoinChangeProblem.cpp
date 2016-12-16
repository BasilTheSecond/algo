//
#include <cstdio>
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

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

private:
	int m_n;
	std::vector<int> m_coins;
};

//

TheCoinChangeProblem::TheCoinChangeProblem(int n, const std::vector<int>& coins) :
m_n(n),
m_coins(coins)
{
	std::sort(m_coins.begin(), m_coins.end());
}

//

TheCoinChangeProblem::~TheCoinChangeProblem()
{
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
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

