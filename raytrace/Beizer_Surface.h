#pragma once
#include "Point.h"
#include <vector>
using namespace std;

class Beizer_Surface
{
	vector3<double> **controlled_points;
	int line, row;
public:
	double du = 0.011f, dv = 0.011f;
	Beizer_Surface(int input_line, int input_row);           //指定biezer_surface几行几列
	void set_control_point(int x, int y, vector3<double> input);        //设置第x行第y列
	vector3<double> get_point(double u, double v);                   //获得参数为u, v的曲面上的点
	void generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes);         //产生曲面所对应的网格
	void output_obj();                 //输出obj文件
	~Beizer_Surface();
};