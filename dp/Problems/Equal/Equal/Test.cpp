#include <vector>
#include <iostream>

// 

class Equal
{
public:
	Equal(const std::vector<int>& numberOfChocolates);
	~Equal();
	void mPrintNumberOfChocolates();

private:
	std::vector<int> m_numberOfChocolates;
};

//

Equal::Equal(const std::vector<int>& numberOfChocolates):
m_numberOfChocolates(numberOfChocolates)
{
}

//

Equal::~Equal()
{
}

//

void 
Equal::mPrintNumberOfChocolates()
{
	for (const auto& numberOfChoclolates : m_numberOfChocolates)
	{
		std::cout << numberOfChoclolates << " ";
	}
}

//

int
main()
{
	Equal equal1({ 2, 2, 3, 7 });
	equal1.mPrintNumberOfChocolates();
	getchar();
	return 0;
}
