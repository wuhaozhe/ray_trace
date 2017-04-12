#pragma once
#include "Object.h"
#include "Point.h"
class Plane : public Object
{
private:
	void init();
public:
	Plane();
	~Plane();
	double A, B, C, D;                 //平面方程的四个参数
	vector3<double> normal_vector;             //平面的法向量
	vector3<double> passed_point;              //平面经过的点
	Plane(vector3<double> input_point, vector3<double> input_normal_vector);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Single_Light light, vector3<double> &in);
};