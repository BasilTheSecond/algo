#include "stdafx.h"
#include <iostream>

class EditDistance
{
public:
	EditDistance();
	~EditDistance();
};

int _tmain(int argc, _TCHAR* argv[])
{
	std::cout << "Press any key to exit" << std::endl;
	EditDistance editDistance;
	getchar();
	return 0;
}

EditDistance::EditDistance()
{
}

EditDistance::~EditDistance()
{
}

