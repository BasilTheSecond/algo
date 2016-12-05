#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class TextJustification
{
public:
	TextJustification(const std::string& text, int lineWidth);
	~TextJustification();
	void mPrintWords();
	
private:
	void mSplitText(const std::string& text);

private:
	std::vector<std::string> m_words;
	const int m_lineWidth;
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::string text("It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).");
	int lineWidth = 80;
	TextJustification textJustification(text, lineWidth);
	getchar();
	return 0;
}

TextJustification::TextJustification(const std::string& text, int lineWidth) :
	m_lineWidth(lineWidth)
{
	mSplitText(text);
	mPrintWords();
}

TextJustification::~TextJustification()
{
}

void TextJustification::mSplitText(const std::string& text)
{
	std::stringstream ss(text);
	std::string word;
	char delim = ' ';
	while (std::getline(ss, word, delim))
	{
		m_words.push_back(word);
	}
}

void TextJustification::mPrintWords()
{
	std::cout << "Text size: " << m_words.size() << " words" << std::endl;
	for (size_t i = 0; i < m_words.size(); i++)
	{
		std::cout << "[" << i << "]: " << m_words[i] << std::endl;
	}
}
