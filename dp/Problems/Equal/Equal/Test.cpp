#include <vector>
#include <iostream>

// 

class Equal
{
public:
	Equal(const std::vector<int>& numberOfChocolates);
	~Equal();
	friend std::ostream& operator<<(std::ostream& os, Equal& equal);

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

std::ostream& 
operator<<(std::ostream& os, Equal& equal)
{
	os << "[ ";
	for (const auto& numberOfChoclolates : equal.m_numberOfChocolates)
	{
		os << numberOfChoclolates << " ";
	}
	os << "]";
	return os;
}

//

int
main()
{
	Equal equal1({ 2, 2, 3, 7 });
	std::cout << equal1 << std::endl;
	getchar();
	return 0;
}
