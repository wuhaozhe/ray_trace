#pragma once
#include <random>
using namespace std;
class MyRand
{
	static default_random_engine e;
	static uniform_real_distribution<double> u;
public:
	static double get_randrom();
};

