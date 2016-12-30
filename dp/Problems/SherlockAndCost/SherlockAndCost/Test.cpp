//

#include <cstdio>
#include <vector>
#include <iostream>

//

class SherlockAndCost
{
public:
	SherlockAndCost();
	SherlockAndCost(const std::vector<int> b);
	int mGetResult() const;
	friend std::ostream& operator<<(std::ostream& os, SherlockAndCost& sherlockAndCost);

private:
	std::vector<int> m_b;
	int m_result;
};

//

SherlockAndCost::SherlockAndCost()
{
}

//

SherlockAndCost::SherlockAndCost(const std::vector<int> b):
m_b(b),
m_result(-1)
{
}

//

int 
SherlockAndCost::mGetResult() const
{
	return m_result;
}

//

std::ostream&
operator<<(std::ostream& os, SherlockAndCost& sherlockAndCost)
{
	os << "[ ";
	for (size_t i = 0; i < sherlockAndCost.m_b.size(); i++)
	{
		os << sherlockAndCost.m_b[i] << " ";
	}
	os << "]";
	return os;
}

//

int 
main()
{
	std::cout << "Test1" << std::endl;
	SherlockAndCost sherlockAndCost1({ 10, 1, 10, 1, 10 });
	std::cout << sherlockAndCost1 << std::endl;
	std::cout << sherlockAndCost1.mGetResult() << std::endl;
	std::cout << (sherlockAndCost1.mGetResult() == 36 ? "PASS" : "FAIL") << std::endl;
	getchar();
	return 0;
}
