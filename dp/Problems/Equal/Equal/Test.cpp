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
	double result = std::numeric_limits<double>::max();
	for (int i = 0; result == std::numeric_limits<double>::max(); i++)
	{
		std::vector<int> finalDistribution;
		finalDistribution.assign(m_initialDistribution.size(), max + i);
		if (i == 0 && finalDistribution == m_initialDistribution)
		{
			m_minNumberOfSteps = 0;
			return;
		}
		std::vector<double> r;
		for (int j = 0; j < finalDistribution.size(); j++)
		{
			r.push_back(mDp(finalDistribution, j, 1));
		}
		for (int j = 0; j < finalDistribution.size(); j++)
		{
			r.push_back(mDp(finalDistribution, j, 2));
		}
		for (int j = 0; j < finalDistribution.size(); j++)
		{
			r.push_back(mDp(finalDistribution, j, 5));
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
		r.push_back(mDp(distribution, i, 1));
	}
	for (int i = 0; i < distribution.size(); i++)
	{
		r.push_back(mDp(distribution, i, 2));
	}
	for (int i = 0; i < distribution.size(); i++)
	{
		r.push_back(mDp(distribution, i, 5));
	}
	double result = *std::min_element(r.begin(), r.end());
	if (result != std::numeric_limits<double>::max())
	{
		result++;
	}
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
	if (equal0.mGetMinNumberOfSteps() == 0)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	std::cout << "Test 1" << std::endl;
	Equal equal1({ 2, 1 });
	std::cout << equal1 << std::endl;
	std::cout << "min number of steps: " << equal1.mGetMinNumberOfSteps() << std::endl;
	if (equal1.mGetMinNumberOfSteps() == 1)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	std::cout << "Test 2" << std::endl;
	Equal equal2({ 2, 2, 3, 7 });
	std::cout << equal2 << std::endl;
	std::cout << "min number of steps: " << equal2.mGetMinNumberOfSteps() << std::endl;
	if (equal2.mGetMinNumberOfSteps() == 2)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	//std::cout << "Test 3" << std::endl;
	//Equal equal3({ 53, 361, 188, 665, 786, 898, 447, 562, 272, 123, 229, 629, 670, 848, 994, 54, 822, 46, 208, 17, 449, 302, 466, 832, 931, 778, 156, 39, 31, 777, 749, 436, 138, 289, 453, 276, 539, 901, 839, 811, 24, 420, 440, 46, 269, 786, 101, 443, 832, 661, 460, 281, 964, 278, 465, 247, 408, 622, 638, 440, 751, 739, 876, 889, 380, 330, 517, 919, 583, 356, 83, 959, 129, 875, 5, 750, 662, 106, 193, 494, 120, 653, 128, 84, 283, 593, 683, 44, 567, 321, 484, 318, 412, 712, 559, 792, 394, 77, 711, 977, 785, 146, 936, 914, 22, 942, 664, 36, 400, 857 });
	//std::cout << equal3 << std::endl;
	//std::cout << "min number of steps: " << equal3.mGetMinNumberOfSteps() << std::endl;
	//if (equal3.mGetMinNumberOfSteps() == 10605)
	//{
	//	std::cout << "PASS" << std::endl;
	//}
	//else
	//{
	//	std::cout << "FAIL" << std::endl;
	//}
	getchar();
	return 0;
}
