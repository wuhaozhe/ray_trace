#pragma once
#include <vector>
#include "Point.h"
#include <assert.h>
using namespace std;

class Beizer_Line               //实现了Beizer曲线
{
private:
	vector<vector3<double> > controlled_point;               //beizer曲线的控制点
	static double Bernstein(double t, int param_i, int param_n);
public:
	static double Bernstein_Derivative(double t, int param_i, int param_n);         //t为参数, i, n为bernstein多项式的参数
	vector3<double> Beizer_Derivative(double t);
	vector3<double> get_point(double t);                    //使用de Casteljau算法求出参数t所对应的点
	void add_control_point(vector3 <double> input_point);               //添加一个控制点
	Beizer_Line();
	~Beizer_Line();
};

