#pragma once
#include "Point.h"

class Beizer_Surface
{
	vector3<double> **controlled_points;
	int line, row;
public:
	Beizer_Surface(int input_line, int input_row);           //指定biezer_surface几行几列
	void set_control_point(int x, int y, vector3<double> input);        //设置第x行第y列
	vector3<double> get_point(double u, double v);                   //获得参数为u, v的曲面上的点
	~Beizer_Surface();
};