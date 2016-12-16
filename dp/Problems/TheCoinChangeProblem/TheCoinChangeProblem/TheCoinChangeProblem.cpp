//
#include <cstdio>
#include <iostream>
#include <vector>

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
	const std::vector<int> m_coins;
};

TheCoinChangeProblem::TheCoinChangeProblem(int n, const std::vector<int>& coins) :
m_n(n),
m_coins(coins)
{
}

TheCoinChangeProblem::~TheCoinChangeProblem()
{
}

int 
main()
{
	//int n, m;
	//std::vector<int> coins;
	//std::cin >> n >> m;
	//for (int i = 0; i < m; i++)
	//{
	//	int c;
	//	std::cin >> c;
	//	coins.push_back(c);
	//}
	int n1 = 4;
	std::vector<int> coins1 = { 1, 2, 3 };
	TheCoinChangeProblem theCoinChangeProblem1(n1, coins1);
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

