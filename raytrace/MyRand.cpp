#include "MyRand.h"

default_random_engine MyRand::e;
uniform_real_distribution<double> MyRand::u = uniform_real_distribution<double>(0, 1);

double MyRand::get_randrom()
{
	return u(e);
}