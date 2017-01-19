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

class StringStack : std::stack<std::string>
{
public:
	StringStack();
	virtual ~StringStack();
	void mPush(const std::string& operation);
	std::string mPop();
	int mSize();
};

//

class IntegerStack : std::stack<int>
{
public:
	IntegerStack();
	virtual ~IntegerStack();
	void mPush(int operand);
	int mPop();
	int mSize();
};

//

class TokenStack : std::stack<Token>
{
public:
	TokenStack();
	virtual ~TokenStack();
	void mPush(const Token& token);
	Token mPop();
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
	void mRemoveBrackets();

private:
	class EvaluateExpressionNoBrackets
	{
	public:
		EvaluateExpressionNoBrackets(const std::vector<Token>& tokens);
		int mGetResult();

	private:
		void mInitialize();
		void mEvaluateInOrderOfPrecedence();
		void mEvaluateOperation(const std::string& operation);

	private:
		std::vector<Token> m_tokens;
		IntegerStack m_operands;
		StringStack m_operations;
		IntegerStack m_tempOperands;
		StringStack m_tempOperations;
		int m_result;
	};

private:
	std::string m_expression;
	std::vector<Token> m_tokens;
	TokenStack m_tokenStack;
	TokenStack m_tempTokenStack;
	int m_result;
};

//

StringStack::StringStack() :
std::stack<std::string>()
{
}

//

StringStack::~StringStack()
{
}

//

void 
StringStack::mPush(const std::string& operation)
{
	push(operation);
}

//

std::string 
StringStack::mPop()
{
	std::string operation = top();
	pop();
	return operation;
}

//

int
StringStack::mSize()
{
	return static_cast<int>(size());
}

//

IntegerStack::IntegerStack() :
std::stack<int>()
{
}

//

IntegerStack::~IntegerStack()
{
}

//

void
IntegerStack::mPush(int operand)
{
	push(operand);
}

//

int
IntegerStack::mPop()
{
	int operand = top();
	pop();
	return operand;
}

//

int
IntegerStack::mSize()
{
	return static_cast<int>(size());
}

//

TokenStack::TokenStack() :
std::stack<Token>()
{
}

//

TokenStack::~TokenStack()
{
}

//

void
TokenStack::mPush(const Token& token)
{
	push(token);
}

//

Token
TokenStack::mPop()
{
	Token& token = top();
	pop();
	return token;
}

//

int
TokenStack::mSize()
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
	mRemoveBrackets();
	EvaluateExpressionNoBrackets evaluateExpressionNoBrackets(m_tokens);
	m_result = evaluateExpressionNoBrackets.mGetResult();
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
		if (s == "/" || s == "*" || s == "+" || s == "-")
		{
			m_tokens.push_back(Token("OPERATOR", s));
		}
		else if (s == "(")
		{
			m_tokens.push_back(Token("LBRACKET", s));
		}
		else if (s == ")")
		{
			m_tokens.push_back(Token("RBRACKET", s));
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
	return m_result;
}

//

void 
EvaluateExpression::mRemoveBrackets()
{
}

//

void
EvaluateExpression::mInitialize()
{
	for (int i = static_cast<int>(m_tokens.size() - 1); i >= 0; i--)
	{
		Token& t = m_tokens[i];
		m_tokenStack.mPush(t);
	}
}

//

EvaluateExpression::EvaluateExpressionNoBrackets::EvaluateExpressionNoBrackets(const std::vector<Token>& tokens) :
m_tokens(tokens),
m_result(-10000)
{
	mInitialize();
	mEvaluateInOrderOfPrecedence();
}

//

void 
EvaluateExpression::EvaluateExpressionNoBrackets::mInitialize()
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
EvaluateExpression::EvaluateExpressionNoBrackets::mGetResult()
{
	return m_result;
}

//

void 
EvaluateExpression::EvaluateExpressionNoBrackets::mEvaluateInOrderOfPrecedence()
{
	mEvaluateOperation("/");
	mEvaluateOperation("*");
	mEvaluateOperation("+");
	mEvaluateOperation("-");
	m_result = m_operands.mPop();
}

//

void 
EvaluateExpression::EvaluateExpressionNoBrackets::mEvaluateOperation(const std::string& operation)
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
