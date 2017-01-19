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

class Operations : std::stack<std::string>
{
public:
	Operations();
	virtual ~Operations();
	void mPush(const std::string& operation);
	std::string mPop();
	int mSize();
};

//

class Operands : std::stack<int>
{
public:
	Operands();
	virtual ~Operands();
	void mPush(int operand);
	int mPop();
	int mSize();
};

//

class EvaluateExpression
{
public:
	EvaluateExpression(const std::string& expression);
	int mGetResult();

private:
	void mTokenizeExpression();
	void mInitialize();
	void mEvaluateInOrderOfPrecedence();
	void mEvaluateOperation(const std::string& operation);

private:
	std::string m_expression;
	std::vector<Token> m_tokens;
	Operands m_operands;
	Operations m_operations;
	Operands m_tempOperands;
	Operations m_tempOperations;
	int m_result;
};

//

Operations::Operations() :
std::stack<std::string>()
{
}

//

Operations::~Operations()
{
}

//

void 
Operations::mPush(const std::string& operation)
{
	push(operation);
}

//

std::string 
Operations::mPop()
{
	std::string operation = top();
	pop();
	return operation;
}

//

int
Operations::mSize()
{
	return static_cast<int>(size());
}

//

Operands::Operands() :
std::stack<int>()
{
}

//

Operands::~Operands()
{
}

//

void
Operands::mPush(int operand)
{
	push(operand);
}

//

int
Operands::mPop()
{
	int operand = top();
	pop();
	return operand;
}

//

int
Operands::mSize()
{
	return static_cast<int>(size());
}

//

Token::Token(const std::string& name, const std::string& value) :
m_name(name),
m_value(value)
{
}

//

EvaluateExpression::EvaluateExpression(const std::string& expression) :
m_expression(expression),
m_result(-10000)
{
	mTokenizeExpression();
	mInitialize();
	mEvaluateInOrderOfPrecedence();
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

void 
EvaluateExpression::mInitialize()
{
	for (int i = static_cast<int>(m_tokens.size() - 1); i >= 0; i--)
	{
		Token& t = m_tokens[i];
		if (t.m_name == "OPERATOR")
		{
			m_operations.mPush(t.m_value);
		}
		else
		{
			m_operands.mPush(std::stoi(t.m_value));
		}
	}
}

//

int 
EvaluateExpression::mGetResult()
{
	return m_result;
}

//

void 
EvaluateExpression::mEvaluateInOrderOfPrecedence()
{
	mEvaluateOperation("/");
	mEvaluateOperation("*");
	mEvaluateOperation("+");
	mEvaluateOperation("-");
	m_result = m_operands.mPop();
}

//

void 
EvaluateExpression::mEvaluateOperation(const std::string& operation)
{
	while (m_operations.mSize() > 0)
	{
		std::string& o = m_operations.mPop();
		int op1 = m_operands.mPop();
		if (o == operation)
		{
			int op2 = m_operands.mPop();
			int result;
			if (o == "/")
			{
				result = op1 / op2;
			}
			else if (o == "*")
			{
				result = op1 * op2;
			}
			else if (o == "+")
			{
				result = op1 + op2;
			}
			else if (o == "-")
			{
				result = op1 - op2;
			}
			m_operands.mPush(result);
		}
		else
		{
			m_tempOperations.mPush(o);
			m_tempOperands.mPush(op1);
		}
	}
	while (m_tempOperations.mSize() > 0)
	{
		std::string& o = m_tempOperations.mPop();
		int op = m_tempOperands.mPop();
		m_operations.mPush(o);
		m_operands.mPush(op);
	}
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
	getchar();
  return 0;
}
