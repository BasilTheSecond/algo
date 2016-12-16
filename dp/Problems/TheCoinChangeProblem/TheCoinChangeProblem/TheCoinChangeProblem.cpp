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

int 
main()
{
	int n, m;
	std::vector<int> coins;
	std::cin >> n >> m;
	for (int i = 0; i < m; i++)
	{
		int c;
		std::cin >> c;
		coins.push_back(c);
	}
	std::cout << "Press any key to exit..." << std::endl;
	getchar();
	return 0;
}

