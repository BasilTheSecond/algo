#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

// 

class Equal
{
public:
	Equal(const std::vector<__int64>& initialDistribution);
	~Equal();
	friend std::ostream& operator<<(std::ostream& os, const Equal& equal);
	__int64 mGetMinNumberOfSteps() const;

private:
	std::vector<__int64> m_initialDistribution;
	__int64 m_minNumberOfSteps;
};

//

Equal::Equal(const std::vector<__int64>& initialDistribution) :
m_initialDistribution(initialDistribution),
m_minNumberOfSteps(0)
{
	__int64 minElement = *std::min_element(m_initialDistribution.begin(), m_initialDistribution.end());
	std::vector<__int64> delta;
	for (int i = 0; i < initialDistribution.size(); i++)
	{
		delta.push_back(initialDistribution[i] - minElement);
	}
	std::vector<__int64> zero;
	zero.assign(delta.size(), 0);
	for (m_minNumberOfSteps = 0; delta != zero; m_minNumberOfSteps++)
	{
		std::vector<__int64>::iterator it = std::max_element(delta.begin(), delta.end());
		__int64 maxArg = it - delta.begin();
		__int64 dec;
		if (*it >= 5)
		{
			dec = 5;
		}
		else if (*it >= 2)
		{
			dec = 2;
		}
		else
		{
			dec = 1;
		}
		delta[maxArg] -= (*it >= 5 ? 5 : (*it >= 2 ? 2 : 1));
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

__int64
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
	std::cout << "Test 4" << std::endl;
	Equal equal4({ 520, 862, 10, 956, 498, 956, 991, 542, 523, 664, 378, 194, 76, 90, 753, 868, 837, 830, 932, 814, 616, 78, 103, 882, 452, 397, 899, 488, 149, 108, 723, 22, 323, 733, 330, 821, 41, 322, 715, 917, 986, 93, 111, 63, 535, 864, 931, 372, 47, 215, 539, 15, 294, 642, 897, 98, 391, 796, 939, 540, 257, 662, 562, 580, 747, 893, 401, 789, 215, 468, 58, 553, 561, 169, 616, 448, 385, 900, 173, 432, 115, 712 });
	std::cout << equal4 << std::endl;
	std::cout << "min number of steps: " << equal4.mGetMinNumberOfSteps() << std::endl;
	if (equal4.mGetMinNumberOfSteps() == 8198)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	std::cout << "Test 5" << std::endl;
	Equal equal5({ 761, 706, 697, 212, 97, 845, 151, 637, 102, 165, 200, 34, 912, 445, 435, 53, 12, 255, 111, 565, 816, 632, 534, 617, 18, 786, 790, 802, 253, 502, 602, 15, 208, 651, 227, 305, 848, 730, 294, 303, 895, 846, 337, 159, 291, 125, 565, 655, 380, 28, 221, 549, 13, 107, 166, 31, 245, 308, 185, 498, 810, 139, 865, 370, 790, 444, 27, 639, 174, 321, 294, 421, 168, 631, 933, 811, 756, 498, 467, 137, 878, 40, 686, 891, 499, 204, 274, 744, 512, 460, 242, 674, 599, 108, 396, 742, 552, 423, 733, 79, 96, 27, 852, 264, 658, 785, 76, 415, 635, 895, 904, 514, 935, 942, 757, 434, 498, 32, 178, 10, 844, 772, 36, 795, 880, 432, 537, 785, 855, 270, 864, 951, 649, 716, 568, 308, 854, 996, 75, 489, 891, 331, 355, 178, 273, 113, 612, 771, 497, 142, 133, 341, 914, 521, 488, 147, 953, 26, 284, 160, 648, 500, 463, 298, 568, 31, 958, 422, 379, 385, 264, 622, 716, 619, 800, 341, 732, 764, 464, 581, 258, 949, 922, 173, 470, 411, 672, 423, 789, 956, 583, 789, 808, 46, 439, 376, 430, 749, 151, });
	std::cout << equal4 << std::endl;
	std::cout << "min number of steps: " << equal5.mGetMinNumberOfSteps() << std::endl;
	if (equal5.mGetMinNumberOfSteps() == 18762)
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
