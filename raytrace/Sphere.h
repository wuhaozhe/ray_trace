#pragma once
#include "Object.h"
#include "Point.h"
class Sphere:public Object
{
private:
	void init();
	double square_radius;                  //半径的平方
public:
	vector3<double> sphere_center;         //球心
	double radius;                        //半径
	Sphere();
	Sphere(vector3<double> input_center, double input_radius);
	bool intersect(Ray input_ray, vector3<double> &intersect_point);
	Color get_color_normalvec(vector3<double> target_pos, vector3<double> view_direction, Light light, vector3<double> &in);
	~Sphere();
};