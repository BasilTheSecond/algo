// BellmanFord.cpp
//

#include "stdafx.h"
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>

void iterativeBellmanFord();
void recursiveBellmanFord();
int deltaSS(int k);
int deltaSA(int k);
int deltaSB(int k);
int deltaSC(int k);
int deltaSD(int k);
int deltaSE(int k);
const int inf = std::numeric_limits<int>::max();
const int wSS = 0;
const int wSA = 10;
const int wSE = 8;
const int wED = 1;
const int wDA = -4;
const int wDC = -1;
const int wAC = 2;
const int wCB = -2;
const int wBA = 1;
std::vector<int> dSS;
std::vector<int> dSA;
std::vector<int> dSB;
std::vector<int> dSC;
std::vector<int> dSD;
std::vector<int> dSE;
std::map<int, int> memdSA;
std::map<int, int> memdSB;
std::map<int, int> memdSC;
std::map<int, int> memdSD;
std::map<int, int> memdSE;
std::map<char, char> parent;

int _tmain(int argc, _TCHAR* argv[])
{
	iterativeBellmanFord();
	recursiveBellmanFord();
	getchar();
	return 0;
}

void iterativeBellmanFord()
{
	std::cout << "iterativeBellmanFord" << std::endl;
	dSS.push_back(0);
	dSA.push_back(inf);
	dSB.push_back(inf);
	dSC.push_back(inf);
	dSD.push_back(inf);
	dSE.push_back(inf);
	for (int k = 1; k <= 5; k++)
	{
		dSS.push_back(0);
		dSA.push_back(std::min(dSD[k - 1] != inf ? dSD[k - 1] + wDA : inf,
									std::min(dSB[k - 1] != inf ? dSB[k - 1] + wBA : inf,
														dSS[k - 1] != inf ? dSS[k - 1] + wSA : inf)));
		if (dSA[k] != inf)
		{
			if (dSD[k - 1] != inf && dSA[k] == dSD[k - 1] + wDA)
			{
				parent['A'] = 'D';
			}
			else if (dSB[k - 1] != inf && dSA[k] == dSB[k - 1] + wBA)
			{
				parent['A'] = 'B';
			}
			else if (dSS[k - 1] != inf && dSA[k] == dSS[k - 1] + wSA)
			{
				parent['A'] = 'S';
			}
		}
		dSB.push_back(dSC[k - 1] != inf ? dSC[k - 1] + wCB : inf);
		if (dSB[k] != inf)
		{
			if (dSC[k - 1] != inf)
			{
				parent['B'] = 'C';
			}
		}
		dSC.push_back(std::min(dSD[k - 1] != inf ? dSD[k - 1] + wDC : inf,
														dSA[k - 1] != inf ? dSA[k - 1] + wAC : inf));
		if (dSC[k] != inf)
		{
			if (dSD[k - 1] != inf && dSC[k] == dSD[k - 1] + wDC)
			{
				parent['C'] = 'D';
			}
			else if (dSA[k - 1] != inf && dSC[k] == dSA[k - 1] + wAC)
			{
				parent['C'] = 'A';
			}
		}
		dSD.push_back(dSE[k - 1] != inf ? dSE[k - 1] + wED : inf);
		if (dSD[k] != inf)
		{
			if (dSE[k - 1] != inf)
			{
				parent['D'] = 'E';
			}
		}
		dSE.push_back(dSS[k - 1] != inf ? dSS[k - 1] + wSE : inf);
		if (dSE[k] != inf)
		{
			if (dSS[k - 1] != inf)
			{
				parent['E'] = 'S';
			}
		}
	}
	std::cout << "delta(S,S)=" << dSS[5] << std::endl;
	std::cout << "delta(S,A)=" << dSA[5] << std::endl;
	for (char c = 'A'; true; c = parent[c])
	{
		std::cout << c;
		if (c == 'S')
		{
			std::cout << std::endl;
			break;
		}
		else
		{
			std::cout << "<-";
		}
	}
	std::cout << "delta(S,B)=" << dSB[5] << std::endl;
	for (char c = 'B'; true; c = parent[c])
	{
		std::cout << c;
		if (c == 'S')
		{
			std::cout << std::endl;
			break;
		}
		else
		{
			std::cout << "<-";
		}
	}
	std::cout << "delta(S,C)=" << dSC[5] << std::endl;
	for (char c = 'C'; true; c = parent[c])
	{
		std::cout << c;
		if (c == 'S')
		{
			std::cout << std::endl;
			break;
		}
		else
		{
			std::cout << "<-";
		}
	}
	std::cout << "delta(S,D)=" << dSD[5] << std::endl;
	for (char c = 'D'; true; c = parent[c])
	{
		std::cout << c;
		if (c == 'S')
		{
			std::cout << std::endl;
			break;
		}
		else
		{
			std::cout << "<-";
		}
	}
	std::cout << "delta(S,E)=" << dSE[5] << std::endl;
	for (char c = 'E'; true; c = parent[c])
	{
		std::cout << c;
		if (c == 'S')
		{
			std::cout << std::endl;
			break;
		}
		else
		{
			std::cout << "<-";
		}
	}
}

void recursiveBellmanFord()
{
	std::cout << "recursiveBellmanFord" << std::endl;
	memdSA[0] = inf;
	memdSB[0] = inf;
	memdSC[0] = inf;
	memdSD[0] = inf;
	memdSE[0] = inf;
	std::cout << "delta(S,S)=" << deltaSS(5) << std::endl;
	std::cout << "delta(S,A)=" << deltaSA(5) << std::endl;
	std::cout << "delta(S,B)=" << deltaSB(5) << std::endl;
	std::cout << "delta(S,C)=" << deltaSC(5) << std::endl;
	std::cout << "delta(S,D)=" << deltaSD(5) << std::endl;
	std::cout << "delta(S,E)=" << deltaSE(5) << std::endl;
}

int deltaSS(int k)
{
	return 0;
}

int deltaSA(int k)
{
	if (memdSA.find(k) == memdSA.end())
	{
		int d1 = deltaSD(k - 1);
		if (d1 != inf)
		{
			d1 += wDA;
		}
		int d2 = deltaSB(k - 1);
		if (d2 != inf)
		{
			d2 += wBA;
		}
		int d3 = deltaSS(k - 1);
		if (d3 != inf)
		{
			d3 += wSA;
		}
		memdSA[k] = std::min(d1,
								std::min(d2,
													d3));
	}
	return memdSA[k];
}

int deltaSB(int k)
{
	if (memdSB.find(k) == memdSB.end())
	{
		int d = deltaSC(k - 1);
		if (d != inf)
		{
			d += wCB;
		}
		memdSB[k] = d;
	}
	return memdSB[k];
}

int deltaSC(int k)
{
	if (memdSC.find(k) == memdSC.end())
	{
		int d1 = deltaSD(k - 1);
		if (d1 != inf)
		{
			d1 += wDC;
		}
		int d2 = deltaSA(k - 1);
		if (d2 != inf)
		{
			d2 += wAC;
		}
		memdSC[k] = std::min(d1,
													d2);
	}
	return memdSC[k];
}

int deltaSD(int k)
{
	if (memdSD.find(k) == memdSD.end())
	{
		int d = deltaSE(k - 1);
		if (d != inf)
		{
			d += wED;
		}
		memdSD[k] = d;
	}
	return memdSD[k];
}

int deltaSE(int k)
{
	if (memdSE.find(k) == memdSE.end())
	{
		int d = deltaSS(k - 1);
		if (d != inf)
		{
			d += wSE;
		}
		memdSE[k] = d;
	}
	return memdSE[k];
}
