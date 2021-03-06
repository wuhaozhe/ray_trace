#include "Beizer_Line.h"
#include <algorithm>
#include <assert.h>
using namespace std;


Beizer_Line::Beizer_Line()
{
}


Beizer_Line::~Beizer_Line()
{
}

void Beizer_Line::add_control_point(vector3<double> input_point)
{
	controlled_point.push_back(input_point);
}

vector3<double> Beizer_Line::get_point(double t)
{
	vector3<double>* temp_vec1 = new vector3<double>[controlled_point.size()];
	vector3<double>* temp_vec2 = new vector3<double>[controlled_point.size()];
	copy(controlled_point.begin(), controlled_point.end(), temp_vec1);
	for (int i = 0; i < controlled_point.size() - 1; i++)
	{
		if ((i & 1) == 0)              //i是奇数
		{
			for (int j = 0; j < controlled_point.size() - i - 1; j++)
			{
				temp_vec2[j] = temp_vec1[j] * (1 - t) + temp_vec1[j + 1] * t;
			}
		}
		else                         //i是偶数
		{
			for (int j = 0; j < controlled_point.size() - i - 1; j++)
			{
				temp_vec1[j] = temp_vec2[j] * (1 - t) + temp_vec2[j + 1] * t;
			}
		}
	}
	if ((controlled_point.size() & 1) == 0)
	{
		vector3<double> return_vector = temp_vec2[0];
		delete[] temp_vec1;
		delete[] temp_vec2;
		return return_vector;
	}
	else
	{
		vector3<double> return_vector = temp_vec1[0];
		delete[] temp_vec1;
		delete[] temp_vec2;
		return return_vector;
	}
}

double Beizer_Line::Bernstein(double t, int param_i, int param_n)
{
	if (param_i < 0 || param_i > param_n)
	{
		return 0;
	}
	if (param_n == 1)
	{
		if (param_i == 0)
		{
			return 1 - t;
		}
		else
		{
			return t;
		}
	}
	return (1 - t) * Bernstein(t, param_i, param_n - 1) + t * Bernstein(t, param_i - 1, param_n - 1);
}

double Beizer_Line::Bernstein_Derivative(double t, int param_i, int param_n)      
{
	assert(param_i >= 0 && param_i <= param_n);
	//递归的求解
	if (param_i == 0)
	{
		return param_n * -1 * Bernstein(t, param_i, param_n - 1);
	}
	if(param_i == param_n)
	{
		return param_n * Bernstein(t, param_i - 1, param_n - 1);
	}
	return param_n * (Bernstein(t, param_i - 1, param_n - 1) - Bernstein(t, param_i, param_n - 1));
}

vector3<double> Beizer_Line::Beizer_Derivative(double t)
{
	vector3<double> return_value = vector3<double>(0, 0, 0);
	for (int i = 0; i < controlled_point.size(); i++)
	{
		return_value = return_value + controlled_point[i] * Bernstein_Derivative(t, i, controlled_point.size() - 1);
	}
	return return_value;
}