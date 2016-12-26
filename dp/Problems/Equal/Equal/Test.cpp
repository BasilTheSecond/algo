#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>

// 

class Equal
{
public:
	Equal(const std::vector<int>& initialNumberOfChocolates);
	~Equal();
	friend std::ostream& operator<<(std::ostream& os, Equal& equal);
	int mGetMinNumberOfSteps() const;

private:
	std::string mVectorToString(const std::vector<int>& v);
	int mDp(const std::vector<int>& numberOfChocolates);

private:
	std::vector<int> m_initialNumberOfChocolates;
	std::unordered_map<std::string, int> m_dp;
	int m_minNumberOfSteps;
};

//

Equal::Equal(const std::vector<int>& initialNumberOfChocolates):
m_initialNumberOfChocolates(initialNumberOfChocolates),
m_minNumberOfSteps(0)
{
	int max = *std::max_element(m_initialNumberOfChocolates.begin(), m_initialNumberOfChocolates.end());
	std::vector<int> candidateSolution1;
	candidateSolution1.assign(m_initialNumberOfChocolates.size(), max);
	int minNumberOfSteps = mDp(candidateSolution1);
}

//

Equal::~Equal()
{
}

//

std::ostream& 
operator<<(std::ostream& os, Equal& equal)
{
	os << equal.mVectorToString(equal.m_initialNumberOfChocolates);
	return os;
}

//

std::string
Equal::mVectorToString(const std::vector<int>& v)
{
	std::stringstream ss;
	ss << "[ ";
	for (size_t i = 0; i < v.size(); i++)
	{
		ss << v[i] << " ";
	}
	ss << "]";
	return ss.str();
}

//

int 
Equal::mDp(const std::vector<int>& numberOfChocolates)
{
	//m_dp[mVectorToString(m_initialNumberOfChocolates)] = 0;
	return 0;
}

//

int 
Equal::mGetMinNumberOfSteps() const
{
	return m_minNumberOfSteps;
}

//

int
main()
{
	std::cout << "Test 1" << std::endl;
	Equal equal1({ 2, 2, 3, 7 });
	std::cout << equal1 << std::endl;
	std::cout << "min number of steps: " << equal1.mGetMinNumberOfSteps() << std::endl;
	getchar();
	return 0;
}
