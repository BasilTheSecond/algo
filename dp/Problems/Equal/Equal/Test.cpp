#include <vector>
#include <iostream>
#include <algorithm>
#include <cstdint>

// 

class Equal
{
public:
	Equal(const std::vector<int64_t>& initialDistribution);
	~Equal();
	friend std::ostream& operator<<(std::ostream& os, const Equal& equal);
	int64_t mGetMinNumberOfSteps() const;
	int64_t mGetNumberOfSteps(int64_t base);

private:
	std::vector<int64_t> m_initialDistribution;
	int64_t m_minNumberOfSteps;
};

//

Equal::Equal(const std::vector<int64_t>& initialDistribution) :
m_initialDistribution(initialDistribution),
m_minNumberOfSteps(0)
{
	int64_t minElement = *std::min_element(m_initialDistribution.begin(), m_initialDistribution.end());
	std::vector<int64_t> result;
	for (int64_t base = minElement; base >= minElement - 4 && base >= 0; base--)
	{
		result.push_back(mGetNumberOfSteps(base));
	}
	m_minNumberOfSteps = *std::min_element(result.begin(), result.end());
}

//

int64_t 
Equal::mGetNumberOfSteps(int64_t base)
{
	int64_t ops = 0;
	for (int i = 0; i < m_initialDistribution.size(); i++)
	{
		int64_t delta = m_initialDistribution[i] - base;
		int64_t a = delta / 5;
		int64_t b = (delta % 5) / 2;
		int64_t c = ((delta % 5) % 2) / 1;
		ops += (a + b + c);
	}
	return ops;
}

//

Equal::~Equal()
{
}

//

std::ostream& 
operator<<(std::ostream& os, const Equal& equal)
{
	os << "[ ";
	for (size_t i = 0; i < equal.m_initialDistribution.size(); i++)
	{
		os << equal.m_initialDistribution[i] << " ";
	}
	os << "]";
	return os;
}

//

int64_t
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
	// taken from: https://www.hackerrank.com/challenges/equal
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
	// taken from: https://www.hackerrank.com/challenges/equal
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
	// taken from: https://www.hackerrank.com/challenges/equal
	std::cout << "Test 5" << std::endl;
	Equal equal5({ 761, 706, 697, 212, 97, 845, 151, 637, 102, 165, 200, 34, 912, 445, 435, 53, 12, 255, 111, 565, 816, 632, 534, 617, 18, 786, 790, 802, 253, 502, 602, 15, 208, 651, 227, 305, 848, 730, 294, 303, 895, 846, 337, 159, 291, 125, 565, 655, 380, 28, 221, 549, 13, 107, 166, 31, 245, 308, 185, 498, 810, 139, 865, 370, 790, 444, 27, 639, 174, 321, 294, 421, 168, 631, 933, 811, 756, 498, 467, 137, 878, 40, 686, 891, 499, 204, 274, 744, 512, 460, 242, 674, 599, 108, 396, 742, 552, 423, 733, 79, 96, 27, 852, 264, 658, 785, 76, 415, 635, 895, 904, 514, 935, 942, 757, 434, 498, 32, 178, 10, 844, 772, 36, 795, 880, 432, 537, 785, 855, 270, 864, 951, 649, 716, 568, 308, 854, 996, 75, 489, 891, 331, 355, 178, 273, 113, 612, 771, 497, 142, 133, 341, 914, 521, 488, 147, 953, 26, 284, 160, 648, 500, 463, 298, 568, 31, 958, 422, 379, 385, 264, 622, 716, 619, 800, 341, 732, 764, 464, 581, 258, 949, 922, 173, 470, 411, 672, 423, 789, 956, 583, 789, 808, 46, 439, 376, 430, 749, 151 });
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
	// taken from: https://www.hackerrank.com/challenges/equal
	std::cout << "Test 6" << std::endl;
	Equal equal6({ 134, 415, 784, 202, 34, 584, 543, 119, 701, 7, 700, 959, 956, 975, 484, 426, 738, 508, 201, 527, 816, 136, 668, 624, 535, 108, 1, 965, 857, 152, 478, 344, 567, 262, 546, 953, 199, 90, 72, 900, 449, 773, 211, 758, 100, 696, 536, 838, 204, 738, 717, 21, 874, 385, 997, 761, 845, 998, 78, 703, 502, 557, 47, 421, 819, 945, 375, 370, 35, 799, 622, 837, 924, 834, 595, 24, 882, 483, 862, 438, 221, 931, 811, 448, 317, 809, 561, 162, 159, 640, 217, 662, 197, 616, 435, 368, 562, 162, 739, 949, 962, 713, 786, 238, 899, 733, 263, 781, 217, 477, 220, 790, 409, 383, 590, 726, 192, 152, 240, 352, 792, 458, 366, 341, 74, 801, 709, 988, 964, 800, 938, 278, 514, 76, 516, 413, 810, 131, 547, 379, 609, 119, 169, 370, 502, 112, 448, 695, 264, 688, 399, 408, 498, 765, 749, 925, 918, 458, 913, 234, 611 });
	std::cout << equal6 << std::endl;
	std::cout << "min number of steps: " << equal6.mGetMinNumberOfSteps() << std::endl;
	if (equal6.mGetMinNumberOfSteps() == 16931)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	// taken from: https://www.hackerrank.com/challenges/equal
	std::cout << "Test 7" << std::endl;
	Equal equal7({ 512, 125, 928, 381, 890, 90, 512, 789, 469, 473, 908, 990, 195, 763, 102, 643, 458, 366, 684, 857, 126, 534, 974, 875, 459, 892, 686, 373, 127, 297, 576, 991, 774, 856, 372, 664, 946, 237, 806, 767, 62, 714, 758, 258, 477, 860, 253, 287, 579, 289, 496 });
	std::cout << equal7 << std::endl;
	std::cout << "min number of steps: " << equal7.mGetMinNumberOfSteps() << std::endl;
	if (equal7.mGetMinNumberOfSteps() == 5104)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	std::cout << "Test 8" << std::endl;
	Equal equal8({ 1, 5, 5 });
	std::cout << equal8 << std::endl;
	std::cout << "min number of steps: " << equal8.mGetMinNumberOfSteps() << std::endl;
	if (equal8.mGetMinNumberOfSteps() == 3)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	// TestCase #11 from: https://www.hackerrank.com/challenges/equal
	// 1
	// 4
	// 2 2 3 7
	std::cout << "Test TestCase #11" << std::endl;
	Equal equalTestCaseNumber11({ 2, 2, 3, 7 });
	std::cout << equalTestCaseNumber11 << std::endl;
	std::cout << "min number of steps: " << equalTestCaseNumber11.mGetMinNumberOfSteps() << std::endl;
	if (equalTestCaseNumber11.mGetMinNumberOfSteps() == 2)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	// TestCase #12 from: https://www.hackerrank.com/challenges/equal
	// 1
	// 5
	// 1 5 5 10 10
	std::cout << "Test TestCase #12" << std::endl;
	Equal equalTestCaseNumber12({ 1, 5, 5, 10, 10 });
	std::cout << equalTestCaseNumber12 << std::endl;
	std::cout << "min number of steps: " << equalTestCaseNumber12.mGetMinNumberOfSteps() << std::endl;
	if (equalTestCaseNumber12.mGetMinNumberOfSteps() == 7)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
	// TestCase #13 from: https://www.hackerrank.com/challenges/equal
	// 1
	// 6
	// 2 5 5 5 5 5
	std::cout << "Test TestCase #13" << std::endl;
	Equal equalTestCaseNumber13({ 2, 5, 5, 5, 5, 5 });
	std::cout << equalTestCaseNumber13 << std::endl;
	std::cout << "min number of steps: " << equalTestCaseNumber13.mGetMinNumberOfSteps() << std::endl;
	if (equalTestCaseNumber13.mGetMinNumberOfSteps() == 6)
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
