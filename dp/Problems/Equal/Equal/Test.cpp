#include <vector>
#include <iostream>

// 

class Equal
{
public:
	Equal(const std::vector<int>& initialNumberOfChocolates);
	~Equal();
	friend std::ostream& operator<<(std::ostream& os, Equal& equal);

private:
	std::vector<int> m_initialNumberOfChocolates;
};

//

Equal::Equal(const std::vector<int>& initialNumberOfChocolates):
m_initialNumberOfChocolates(initialNumberOfChocolates)
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
	for (size_t i = 0; i < equal.m_initialNumberOfChocolates.size(); i++)
	{
		os << equal.m_initialNumberOfChocolates[i] << " ";
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
