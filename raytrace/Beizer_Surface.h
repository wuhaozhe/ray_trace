#pragma once
#include "Point.h"

class Beizer_Surface
{
	vector3<double> **controlled_points;
	int line, row;
public:
	Beizer_Surface(int input_line, int input_row);           //ָ��biezer_surface���м���
	void set_control_point(int x, int y, vector3<double> input);        //���õ�x�е�y��
	vector3<double> get_point(double u, double v);                   //��ò���Ϊu, v�������ϵĵ�
	~Beizer_Surface();
};