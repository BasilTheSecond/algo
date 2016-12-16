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
	int n1 = 4;
	std::vector<int> coins1 = { 1, 2, 3 };
	TheCoinChangeProblem theCoinChangeProblem1(n1, coins1);
	int n2 = 10;
	std::vector<int> coins2 = { 2, 5, 3, 6 };
	TheCoinChangeProblem theCoinChangeProblem2(n2, coins2);
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

