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
	friend std::ostream& operator<<(std::ostream& os, const Equal& equal);
	int mGetMinNumberOfSteps() const;

private:
	std::vector<int> m_initialDistribution;
	int m_minNumberOfSteps;
};

//

Equal::Equal(const std::vector<int>& initialDistribution) :
m_initialDistribution(initialDistribution),
m_minNumberOfSteps(0)
{
	int minElement = *std::min_element(m_initialDistribution.begin(), m_initialDistribution.end());
	std::vector<int> delta;
	for (int i = 0; i < initialDistribution.size(); i++)
	{
		delta.push_back(initialDistribution[i] - minElement);
	}
}

//

Equal::~Equal()
{
}

//

std::ostream& 
operator<<(std::ostream& os, const Equal& equal)
{
	std::stringstream ss;
	ss << "[ ";
	for (size_t i = 0; i < equal.m_initialDistribution.size(); i++)
	{
		ss << equal.m_initialDistribution[i] << " ";
	}
	ss << "]";
	return os;
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
	std::cout << "Test 3" << std::endl;
	Equal equal3({ 53, 361, 188, 665, 786, 898, 447, 562, 272, 123, 229, 629, 670, 848, 994, 54, 822, 46, 208, 17, 449, 302, 466, 832, 931, 778, 156, 39, 31, 777, 749, 436, 138, 289, 453, 276, 539, 901, 839, 811, 24, 420, 440, 46, 269, 786, 101, 443, 832, 661, 460, 281, 964, 278, 465, 247, 408, 622, 638, 440, 751, 739, 876, 889, 380, 330, 517, 919, 583, 356, 83, 959, 129, 875, 5, 750, 662, 106, 193, 494, 120, 653, 128, 84, 283, 593, 683, 44, 567, 321, 484, 318, 412, 712, 559, 792, 394, 77, 711, 977, 785, 146, 936, 914, 22, 942, 664, 36, 400, 857 });
	std::cout << equal3 << std::endl;
	std::cout << "min number of steps: " << equal3.mGetMinNumberOfSteps() << std::endl;
	if (equal3.mGetMinNumberOfSteps() == 10605)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	getchar();
	return 0;
}
