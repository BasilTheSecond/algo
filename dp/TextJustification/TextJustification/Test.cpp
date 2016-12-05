#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

void split(const std::string &text, std::vector<std::string>& words) 
{
	std::stringstream ss(text);
	std::string word;
	char delim = ' ';
	while (std::getline(ss, word, delim))
	{
		words.push_back(word);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	std::vector<std::string> words;
	std::string text("It is a long established fact that a reader will be distracted by the readable content of a page when looking at its layout. The point of using Lorem Ipsum is that it has a more-or-less normal distribution of letters, as opposed to using 'Content here, content here', making it look like readable English. Many desktop publishing packages and web page editors now use Lorem Ipsum as their default model text, and a search for 'lorem ipsum' will uncover many web sites still in their infancy. Various versions have evolved over the years, sometimes by accident, sometimes on purpose (injected humour and the like).");
	split(text, words);
	for (std::string word : words)
	{
		std::cout << "[" << word << "]" << std::endl;
	}
	getchar();
	return 0;
}
