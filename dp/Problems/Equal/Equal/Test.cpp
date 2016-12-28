#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>

// 

class Equal
{
public:
	Equal(const std::vector<int>& initialDistribution);
	~Equal();
	friend std::ostream& operator<<(std::ostream& os, Equal& equal);
	int mGetMinNumberOfSteps() const;

private:
	std::string mVectorToString(const std::vector<int>& v);
	double mDp(std::vector<int> distribution, int exception, int decrement);

private:
	std::vector<int> m_initialDistribution;
	std::unordered_map<std::string, int> m_dp;
	int m_minNumberOfSteps;
};

//

Equal::Equal(const std::vector<int>& initialDistribution) :
m_initialDistribution(initialDistribution),
m_minNumberOfSteps(-1)
{
	int max = *std::max_element(m_initialDistribution.begin(), m_initialDistribution.end());
	std::vector<int> candidate;
	candidate.assign(m_initialDistribution.size(), max);
	if (candidate == m_initialDistribution)
	{
		m_minNumberOfSteps = 0;
		return;
	}
	double result = std::numeric_limits<double>::max();
	for (int j = 0; result == std::numeric_limits<double>::max(); j++)
	{
		for (int i = 0; i < candidate.size(); i++)
		{
			candidate[i] += j;
		}
		std::vector<double> r;
		for (int i = 0; i < candidate.size(); i++)
		{
			r.push_back(mDp(candidate, i, 1));
		}
		for (int i = 0; i < candidate.size(); i++)
		{
			r.push_back(mDp(candidate, i, 2));
		}
		for (int i = 0; i < candidate.size(); i++)
		{
			r.push_back(mDp(candidate, i, 5));
		}
		result = *std::min_element(r.begin(), r.end());
	}
	m_minNumberOfSteps = static_cast<int>(result);
}

//

Equal::~Equal()
{
}

//

std::ostream& 
operator<<(std::ostream& os, Equal& equal)
{
	os << equal.mVectorToString(equal.m_initialDistribution);
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

double
Equal::mDp(std::vector<int> distribution, int exception, int decrement)
{
	for (size_t i = 0; i < distribution.size(); i++)
	{
		if (i != exception)
		{
			distribution[i] -= decrement;
			if (distribution[i] < m_initialDistribution[i])
			{
				return std::numeric_limits<double>::max();
			}
		}
	}
	if (distribution == m_initialDistribution)
	{
		return 1;
	}
	std::vector<double> r;
	for (int i = 0; i < distribution.size(); i++)
	{
		r.push_back(mDp(distribution, i, 1) + 1);
	}
	for (int i = 0; i < distribution.size(); i++)
	{
		r.push_back(mDp(distribution, i, 2) + 1);
	}
	for (int i = 0; i < distribution.size(); i++)
	{
		r.push_back(mDp(distribution, i, 5) + 1);
	}
	double result = *std::min_element(r.begin(), r.end());
	return result;
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
	std::cout << "Test 0" << std::endl;
	Equal equal0({ 2, 2, 2, 2, 2, 2 });
	std::cout << equal0 << std::endl;
	std::cout << "min number of steps: " << equal0.mGetMinNumberOfSteps() << std::endl;
	std::cout << "Test 1" << std::endl;
	Equal equal1({ 2, 1 });
	std::cout << equal1 << std::endl;
	std::cout << "min number of steps: " << equal1.mGetMinNumberOfSteps() << std::endl;
	std::cout << "Test 2" << std::endl;
	Equal equal2({ 2, 2, 3, 7 });
	std::cout << equal2 << std::endl;
	std::cout << "min number of steps: " << equal2.mGetMinNumberOfSteps() << std::endl;
	getchar();
	return 0;
}
