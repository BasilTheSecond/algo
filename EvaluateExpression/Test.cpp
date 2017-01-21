//

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

//

class EvaluateExpression
{
public:
	EvaluateExpression(const std::string& expression);
	int mGetResult();
};

//

EvaluateExpression::EvaluateExpression(const std::string& expression)
{
	std::stack<std::string> s;
	std::stringstream ss(expression);
	while (!ss.eof())
	{
		std::string token;
		ss >> token;
		s.push(token);
	}
}

//

int EvaluateExpression::mGetResult()
{
	return -1000;
}

//

class EvaluateExpressionTest
{
public:
	EvaluateExpressionTest(const std::string& testName, const std::string& expression, int expectedResult);
	void mAssert(int result);

private:
	std::string m_testName;
	std::string m_expression;
	int m_expectedResult;
};

//

EvaluateExpressionTest::EvaluateExpressionTest(const std::string& testName, const std::string& expression, int expectedResult) :
m_testName(testName),
m_expression(expression),
m_expectedResult(expectedResult)
{
}

//

void 
EvaluateExpressionTest::mAssert(int result)
{
	std::cout << m_testName << std::endl;
	std::cout << "Expression: " << m_expression << std::endl;
	std::cout << "Expected: " << m_expectedResult << std::endl;
	std::cout << "Actual: " << result << std::endl;
	if (m_expectedResult == result)
	{
		std::cout << "PASS" << std::endl;
	}
	else
	{
		std::cout << "FAIL" << std::endl;
	}
}

//

int 
main()
{
	
	std::string testName1("Test 1");
	std::string expression1("1 + 1");
	int result1 = 2;
	EvaluateExpressionTest evaluateExpressionTest1(testName1, expression1, result1);
	EvaluateExpression evaluateExpression1(expression1);
	evaluateExpressionTest1.mAssert(evaluateExpression1.mGetResult());
	std::string testName2("Test 2");
	std::string expression2("1 + 2 - 3");
	int result2 = 0;
	EvaluateExpressionTest evaluateExpressionTest2(testName2, expression2, result2);
	EvaluateExpression evaluateExpression2(expression2);
	evaluateExpressionTest2.mAssert(evaluateExpression2.mGetResult());
	std::string testName3("Test 3");
	std::string expression3("1 + 2 * 4 / 5 + 6 - 7 / 2 * 3");
	int result3 = -2;
	EvaluateExpressionTest evaluateExpressionTest3(testName3, expression3, result3);
	EvaluateExpression evaluateExpression3(expression3);
	evaluateExpressionTest3.mAssert(evaluateExpression3.mGetResult());
	std::string testName4("Test 4");
	std::string expression4("( 1 + 2 ) * 4 / ( 5 + ( 6 - 7 ) / 2 * 3 )");
	int result4 = 0;
	EvaluateExpressionTest evaluateExpressionTest4(testName4, expression4, result4);
	EvaluateExpression evaluateExpression4(expression4);
	evaluateExpressionTest4.mAssert(evaluateExpression4.mGetResult());
	getchar();
  return 0;
}
