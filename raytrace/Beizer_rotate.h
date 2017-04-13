#pragma once
#include "Beizer_Line.h"
#include "rotate.h"
#include <vector>
using namespace std;
class Beizer_rotate              //实现了Beizer曲线旋转得到的曲面
{
public:
	vector3<double> rotate_axis;             //Beizer曲线所绕着旋转的轴,是单位化了的
	double rotate_angle, beizer_step = 0.01;                 //每次旋转所转的角度与Beizer曲线上t的步长（控制图像的精细程度） 
	Beizer_rotate();                         //默认是按0, 0, 1旋转的
	Beizer_rotate(vector3<double> input_axis);
	~Beizer_rotate();
	void add_control_point(vector3<double> input_point);
	void generate_meshes(vector<vector3<double> > &points, vector<vector3<int> > &meshes);         //产生曲线所对应的网格
	void output_obj();                 //输出obj文件
private:
	Beizer_Line beizer_line;
	Rotate rotate;
};