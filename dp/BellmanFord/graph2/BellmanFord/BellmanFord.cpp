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
		dSB.push_back(dSC[k - 1] != inf ? dSC[k - 1] + wCB : inf);
		dSC.push_back(std::min(dSD[k - 1] != inf ? dSD[k - 1] + wDC : inf,
														dSA[k - 1] != inf ? dSA[k - 1] + wAC : inf));
		dSD.push_back(dSE[k - 1] != inf ? dSE[k - 1] + wED : inf);
		dSE.push_back(dSS[k - 1] != inf ? dSS[k - 1] + wSE : inf);
	}
	std::cout << "delta(S,S)=" << dSS[5] << std::endl;
	std::cout << "delta(S,A)=" << dSA[5] << std::endl;
	std::cout << "delta(S,B)=" << dSB[5] << std::endl;
	std::cout << "delta(S,C)=" << dSC[5] << std::endl;
	std::cout << "delta(S,D)=" << dSD[5] << std::endl;
	std::cout << "delta(S,E)=" << dSE[5] << std::endl;
}

void recursiveBellmanFord()
{
	std::cout << "recursiveBellmanFord" << std::endl;
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
		memdSA[k] = std::min(deltaSD(k - 1) + wDA,
								std::min(deltaSB(k - 1) + wBA,
													deltaSS(k - 1) + wSA));
	}
	return memdSA[k];
}

int deltaSB(int k)
{
	if (memdSB.find(k) == memdSB.end())
	{
		memdSB[k] = deltaSC(k - 1) + wCB;
	}
	return memdSB[k];
}

int deltaSC(int k)
{
	if (memdSC.find(k) == memdSC.end())
	{
		memdSC[k] = std::min(deltaSD(k - 1) + wDC,
													deltaSA(k - 1) + wAC);
	}
	return memdSC[k];
}

int deltaSD(int k)
{
	if (memdSD.find(k) == memdSD.end())
	{
		memdSD[k] = deltaSE(k - 1) + wED;
	}
	return memdSD[k];
}

int deltaSE(int k)
{
	if (memdSE.find(k) == memdSE.end())
	{
		memdSE[k] = deltaSS(k - 1) + wSE;
	}
	return memdSE[k];
}
