// BellmanFord.cpp
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <algorithm>

static void recursiveBellmanFord();
static int deltaAE(int k);
static int deltaBE(int k);
static int deltaCE(int k);
static int deltaDE(int k);
static int deltaFE(int k);
static int deltaEE(int k);
static void iterativeBellmanFord();

static std::vector<int> dAE;
static std::vector<int> dBE;
static std::vector<int> dCE;
static std::vector<int> dDE;
static std::vector<int> dFE;
static std::vector<int> dEE;

static const int inf = std::numeric_limits<int>::max();
static const int wAB = 1;
static const int wBC = 2;
static const int wCD = 3;
static const int wDE = -3;
static const int wEC = 5;
static const int wCF = -1;
static const int wED = 4;
static const int wFA = -1;

int 
_tmain(int argc, _TCHAR* argv[])
{
	recursiveBellmanFord();
	iterativeBellmanFord();
	getchar();
	return 0;
}

static void 
iterativeBellmanFord()
{
	std::cout << "iterativeBellmanFord" << std::endl;
	dAE.push_back(inf);
	dBE.push_back(inf);
	dCE.push_back(inf);
	dDE.push_back(inf);
	dFE.push_back(inf);
	dEE.push_back(0);
	for (int k = 1; k <= 5; k++)
	{
		dAE.push_back(dBE[k - 1] != inf ? wAB + dBE[k - 1] : inf);
		dBE.push_back(dCE[k - 1] != inf ? wBC + dCE[k - 1] : inf);
		dCE.push_back(std::min(dDE[k - 1] != inf ? wCD + dDE[k - 1] : inf, 
														dFE[k - 1] == inf ? wCF + dFE[k - 1] : inf));
		dDE.push_back(dEE[k - 1] != inf ? wDE + dEE[k - 1] : inf);
		dFE.push_back(dAE[k - 1] != inf ? wFA + dAE[k - 1] : inf);
		dEE.push_back(0);
	}
	std::cout << "delta(A,E)=" << dAE[5] << std::endl;
	std::cout << "delta(B,E)=" << dBE[5] << std::endl;
	std::cout << "delta(C,E)=" << dCE[5] << std::endl;
	std::cout << "delta(D,E)=" << dDE[5] << std::endl;
	std::cout << "delta(E,E)=" << dEE[5] << std::endl;
	std::cout << "delta(F,E)=" << dFE[5] << std::endl;
}

static void
recursiveBellmanFord()
{
	std::cout << "recursiveBellmanFord" << std::endl;
	int dAE = deltaAE(5);
	std::cout << "delta(A,E)=" << dAE << std::endl;
	int dBE = deltaBE(5);
	std::cout << "delta(B,E)=" << dBE << std::endl;
	int dCE = deltaCE(5);
	std::cout << "delta(C,E)=" << dCE << std::endl;
	int dDE = deltaDE(5);
	std::cout << "delta(D,E)=" << dDE << std::endl;
	int dEE = deltaEE(5);
	std::cout << "delta(E,E)=" << dEE << std::endl;
	int dFE = deltaFE(5);
	std::cout << "delta(F,E)=" << dFE << std::endl;
}

static int 
deltaAE(int k)
{
	if (k == 0)
	{
		return inf;
	}
	else
	{
		int d = deltaBE(k - 1);
		if (d != inf)
		{
			d += wAB;
		}
		return d;
	}
}

static int
deltaBE(int k)
{
	if (k == 0)
	{
		return inf;
	}
	else
	{
		int d = deltaCE(k - 1);
		if (d != inf)
		{
			d += wBC;
		}
		return d;
	}
}

static int
deltaCE(int k)
{
	if (k == 0)
	{
		return inf;
	}
	else
	{
		int d1 = deltaDE(k - 1);
		if (d1 != inf)
		{
			d1 += wCD;
		}
		int d2 = deltaFE(k - 1);
		if (d2 != inf)
		{
			d2 += wCF;
		}
		return std::min(d1, d2);
	}
}

static int 
deltaDE(int k)
{
	if (k == 0)
	{
		return inf;
	}
	else
	{
		int d = deltaEE(k - 1);
		if (d != inf)
		{
			d += wDE;
		}
		return d;
	}
}

static int 
deltaFE(int k)
{
	if (k == 0)
	{
		return inf;
	}
	else
	{
		int d = deltaAE(k - 1);
		if (d != inf)
		{
			d += wFA;
		}
		return d;
	}
}

static int
deltaEE(int k)
{
	(void)k;
	return 0;
}
