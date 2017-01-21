//

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>
#include <queue>

//

class EvaluateExpression
{
public:
	EvaluateExpression(const std::string& e);
	int mGetResult();

private:
	friend std::ostream& operator<<(std::ostream& os, const std::stack<std::string>& s);
	friend std::ostream& operator<<(std::ostream& os, const std::queue<std::string>& q);
	void mEvaluateExpressionWithoutParanthesis(std::stack<std::string>& expression);
	void mEvaluateExpressionWithoutParanthesis(std::stack<std::string>& expression, const std::string& operation);

private:
	std::string m_result;
};

//

EvaluateExpression::EvaluateExpression(const std::string& e) :
m_result("-1000")
{
	std::stringstream ss(e);
	std::queue<std::string> expression;
	std::stack<std::string> prefix;
	while (!ss.eof())
	{
		std::string token;
		ss >> token;
		expression.push(token);
	}
	while (expression.size() > 0)
	{
		std::string token = expression.front();
		expression.pop();
		if (token == ")")
		{
			std::stack<std::string> subexpression;
			while (prefix.top() != "(")
			{
				subexpression.push(prefix.top());
				prefix.pop();
			}
			prefix.pop(); // pop "("
			mEvaluateExpressionWithoutParanthesis(subexpression);
			prefix.push(subexpression.top());
		}
		else
		{
			prefix.push(token);
		}
	}
	std::stack<std::string> reversePrefix;
	while (prefix.size() > 0)
	{
		reversePrefix.push(prefix.top());
		prefix.pop();
	}
	mEvaluateExpressionWithoutParanthesis(reversePrefix);
	//m_result = reversePrefix.top();
}

//

std::ostream& 
operator<<(std::ostream& os, const std::queue<std::string>& q)
{
	std::queue<std::string> temp = q;
	while (temp.size() > 0)
	{
		os << "[" << temp.front() << "]";
		temp.pop();
	}
	return os;
}

//

std::ostream&
operator<<(std::ostream& os, const std::stack<std::string>& s)
{
	std::stack<std::string> temp = s;
	while (temp.size() > 0)
	{
		os << "[" << temp.top() << "]";
		temp.pop();
	}
	return os;
}

//

int 
EvaluateExpression::mGetResult()
{
	int result;
	std::stringstream ss(m_result);
	ss >> result;
	return result;
}

//

void
EvaluateExpression::mEvaluateExpressionWithoutParanthesis(std::stack<std::string>& expression)
{
	mEvaluateExpressionWithoutParanthesis(expression, "/");
	mEvaluateExpressionWithoutParanthesis(expression, "*");
	mEvaluateExpressionWithoutParanthesis(expression, "+");
	mEvaluateExpressionWithoutParanthesis(expression, "-");
	std::stack<std::string> s;
	s.push(std::string("RESULT"));
	expression = s;
}

//

void 
EvaluateExpression::mEvaluateExpressionWithoutParanthesis(std::stack<std::string>& expression, const std::string& operation)
{
	std::cout << "Evaluate " << operation << " in: " << expression << std::endl;
	std::stack<std::string> prefix;
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
	std::cout << m_testName << std::endl;
	std::cout << "Expression: " << m_expression << std::endl;
	std::cout << "Expected: " << m_expectedResult << std::endl;
}

//

void 
EvaluateExpressionTest::mAssert(int result)
{
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
	std::string testName5("Test 5");
	std::string expression5("( 5 + ( 5 + ( 5 + ( 5 + ( 5 + ( 5 + 5 ) ) ) ) ) )");
	int result5 = 35;
	EvaluateExpressionTest evaluateExpressionTest5(testName5, expression5, result5);
	EvaluateExpression evaluateExpression5(expression5);
	evaluateExpressionTest5.mAssert(evaluateExpression5.mGetResult());
	getchar();
  return 0;
}
