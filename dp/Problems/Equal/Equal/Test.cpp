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

private:
	std::string mVectorToString(const std::vector<int>& v);

private:
	std::vector<int> m_initialNumberOfChocolates;
	std::unordered_map<std::string, int> m_dp;
};

//

Equal::Equal(const std::vector<int>& initialNumberOfChocolates):
m_initialNumberOfChocolates(initialNumberOfChocolates)
{
	int max = *std::max_element(m_initialNumberOfChocolates.begin(), m_initialNumberOfChocolates.end());
	std::vector<int> candidateSolution1;
	candidateSolution1.assign(m_initialNumberOfChocolates.size(), max);
	m_dp[mVectorToString(m_initialNumberOfChocolates)] = 0;
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
main()
{
	Equal equal1({ 2, 2, 3, 7 });
	std::cout << equal1 << std::endl;
	getchar();
	return 0;
}
