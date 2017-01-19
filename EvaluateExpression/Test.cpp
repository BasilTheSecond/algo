//

#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <stack>

//

class Token
{
public:
	Token(const std::string& name, const std::string& value);

public:
	std::string m_name;
	std::string m_value;
};

//

class EvaluateExpression
{
public:
	EvaluateExpression(const std::string& expression);
	int mGetResult();

private:
	void mTokenizeExpression();

private:
	std::string m_expression;
	std::vector<Token> m_tokens;
	std::stack<int> m_operands;
	std::stack<std::string> m_operations;
};

//

Token::Token(const std::string& name, const std::string& value) :
m_name(name),
m_value(value)
{
}

//

EvaluateExpression::EvaluateExpression(const std::string& expression) :
m_expression(expression)
{
	mTokenizeExpression();
	for (int i = static_cast<int>(m_tokens.size() - 1); i >= 0; i--)
	{
		Token& t = m_tokens[i];
		if (t.m_name == "OPERATOR")
		{
			m_operations.push(t.m_value);
		}
		else
		{
			m_operands.push(std::stoi(t.m_value));
		}
	}
	//while (m_operands.size() > 0)
	//{
	//	std::cout << m_operands.top() << std::endl;
	//	m_operands.pop();
	//}
	//while (m_operations.size() > 0)
	//{
	//	std::cout << m_operations.top() << std::endl;
	//	m_operations.pop();
	//}
}

//

void 
EvaluateExpression::mTokenizeExpression()
{
	std::stringstream ss(m_expression);
	while (!ss.eof())
	{
		std::string s;
		ss >> s;
		//std::cout << "[" << s << "]" << std::endl;
		if (s == "/" || s == "*" || s == "+" || s == "-")
		{
			m_tokens.push_back(Token("OPERATOR", s));
		}
		else
		{
			m_tokens.push_back(Token("OPERAND", s));
		}
	}
}

//

int 
EvaluateExpression::mGetResult()
{
	return -10000000;
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
	getchar();
  return 0;
}
