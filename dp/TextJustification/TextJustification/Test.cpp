#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <fstream>

class TextJustification
{
public:
	TextJustification(const std::string& text, int lineWidth);
	TextJustification(std::ifstream& ifile, int lineWidth);
	~TextJustification();
	void mPrintWords();
	void mPrintJustified(std::ofstream& ofile);
	
private:
	void mSplitText(const std::string& text);
	void mCalculateCosts();
	double mCost(int i, int j);

private:
	std::vector<std::string> m_words;
	const int m_lineWidth;
	std::vector<double> m_costs;
	std::vector<int> m_parent;

private:
	static const double k_inf;
};

const double TextJustification::k_inf = std::numeric_limits<double>::max();

int _tmain(int argc, _TCHAR* argv[])
{
	std::ifstream ifile1("unjustified.txt");
	int lineWidth1 = 80;
	TextJustification textJustification1(ifile1, lineWidth1);
	textJustification1.mPrintWords();
	std::ofstream ofile1("justified1.txt");
	textJustification1.mPrintJustified(ofile1);
	std::string text2("It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).");
	int lineWidth2 = 50;
	TextJustification textJustification2(text2, lineWidth2);
	textJustification2.mPrintWords();
	std::ofstream ofile2("justified2.txt");
	textJustification2.mPrintJustified(ofile2);
	getchar();
	return 0;
}

TextJustification::TextJustification(const std::string& text, int lineWidth) :
	m_lineWidth(lineWidth)
{
	mSplitText(text);
	mCalculateCosts();
}

TextJustification::TextJustification(std::ifstream& ifile, int lineWidth) :
	m_lineWidth(lineWidth)
{
	std::stringstream sstream;
	sstream << ifile.rdbuf();
	mSplitText(sstream.str());
	mCalculateCosts();
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

void TextJustification::mCalculateCosts()
{
	m_costs.clear();
	int n = m_words.size();
	m_costs.resize(n + 1);
	m_parent.resize(m_words.size());
	m_costs[n] = 0;
	// subproblem iteration formula:
	// k = n - 1, n - 2, ... 0 (start from the end)
	// costs[k] = min {cost(k, i) + costs[i]}
	//					k < i < n+1
	for (int k = n - 1; k >= 0; k--)
	{
		m_costs[k] = k_inf;
		for (int i = k + 1; i < n + 1; i++)
		{
			double cost = mCost(k, i) + m_costs[i];
			if (cost < k_inf)
			{
				m_parent[k] = i;
			}
			m_costs[k] = std::min(mCost(k, i) + m_costs[i], m_costs[k]);
		}
	}
}

double TextJustification::mCost(int i, int j)
{
	int totalWidth = 0;
	for (int k = i; k < j; k++)
	{
		totalWidth += m_words[k].size();
	}
	totalWidth += (j - i - 1); // space
	int extraSpace = m_lineWidth - totalWidth;
	return extraSpace < 0 ? k_inf : std::pow(extraSpace, 3);
}

void TextJustification::mPrintJustified(std::ofstream& ofile)
{
	for (int i = 0; true; i = m_parent[i])
	{
		for (int j = i; j < m_parent[i]; j++)
		{
			ofile << m_words[j] << ((j < m_parent[i] - 1) ? " " : "\n");
		}
		if (m_parent[i] == m_words.size())
		{
			break;
		}
	}
}
